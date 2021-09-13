#pragma once
#include <opencv2/opencv.hpp>
#include "DM_fit.h"
using namespace cv;

namespace cv_DM
{

	static const double eps = 1e-6;

	static void fitLine2D_wods(const Point2d* points, int count, double *weights, double *line)
	{
		double x = 0, y = 0, x2 = 0, y2 = 0, xy = 0, w = 0;
		double dx2, dy2, dxy;
		int i;
		double t;

		// Calculating the average of x and y...
		if (weights == 0)
		{
			for (i = 0; i < count; i += 1)
			{
				x += points[i].x;
				y += points[i].y;
				x2 += points[i].x * points[i].x;
				y2 += points[i].y * points[i].y;
				xy += points[i].x * points[i].y;
			}
			w = (double)count;
		}
		else
		{
			for (i = 0; i < count; i += 1)
			{
				x += weights[i] * points[i].x;
				y += weights[i] * points[i].y;
				x2 += weights[i] * points[i].x * points[i].x;
				y2 += weights[i] * points[i].y * points[i].y;
				xy += weights[i] * points[i].x * points[i].y;
				w += weights[i];
			}
		}

		x /= w;
		y /= w;
		x2 /= w;
		y2 /= w;
		xy /= w;

		dx2 = x2 - x * x;
		dy2 = y2 - y * y;
		dxy = xy - x * y;

		t = (double)atan2(2 * dxy, dx2 - dy2) / 2;
		line[0] = (double)cos(t);
		line[1] = (double)sin(t);

		line[2] = (double)x;
		line[3] = (double)y;
	}

	static void fitLine3D_wods(const Point3f * points, int count, double *weights, double *line)
	{
		int i;
		double w0 = 0;
		double x0 = 0, y0 = 0, z0 = 0;
		double x2 = 0, y2 = 0, z2 = 0, xy = 0, yz = 0, xz = 0;
		double dx2, dy2, dz2, dxy, dxz, dyz;
		double *v;
		double n;
		double det[9], evc[9], evl[3];

		memset(evl, 0, 3 * sizeof(evl[0]));
		memset(evc, 0, 9 * sizeof(evl[0]));

		if (weights)
		{
			for (i = 0; i < count; i++)
			{
				double x = points[i].x;
				double y = points[i].y;
				double z = points[i].z;
				double w = weights[i];


				x2 += x * x * w;
				xy += x * y * w;
				xz += x * z * w;
				y2 += y * y * w;
				yz += y * z * w;
				z2 += z * z * w;
				x0 += x * w;
				y0 += y * w;
				z0 += z * w;
				w0 += w;
			}
		}
		else
		{
			for (i = 0; i < count; i++)
			{
				double x = points[i].x;
				double y = points[i].y;
				double z = points[i].z;

				x2 += x * x;
				xy += x * y;
				xz += x * z;
				y2 += y * y;
				yz += y * z;
				z2 += z * z;
				x0 += x;
				y0 += y;
				z0 += z;
			}
			w0 = (double)count;
		}

		x2 /= w0;
		xy /= w0;
		xz /= w0;
		y2 /= w0;
		yz /= w0;
		z2 /= w0;

		x0 /= w0;
		y0 /= w0;
		z0 /= w0;

		dx2 = x2 - x0 * x0;
		dxy = xy - x0 * y0;
		dxz = xz - x0 * z0;
		dy2 = y2 - y0 * y0;
		dyz = yz - y0 * z0;
		dz2 = z2 - z0 * z0;

		det[0] = dz2 + dy2;
		det[1] = -dxy;
		det[2] = -dxz;
		det[3] = det[1];
		det[4] = dx2 + dz2;
		det[5] = -dyz;
		det[6] = det[2];
		det[7] = det[5];
		det[8] = dy2 + dx2;

		// Searching for a eigenvector of det corresponding to the minimal eigenvalue
		Mat _det(3, 3, CV_64F, det);
		Mat _evc(3, 3, CV_64F, evc);
		Mat _evl(3, 1, CV_64F, evl);
		eigen(_det, _evl, _evc);
		i = evl[0] < evl[1] ? (evl[0] < evl[2] ? 0 : 2) : (evl[1] < evl[2] ? 1 : 2);

		v = &evc[i * 3];
		n = (double)std::sqrt((double)v[0] * v[0] + (double)v[1] * v[1] + (double)v[2] * v[2]);
		n = (double)MAX(n, eps);
		line[0] = v[0] / n;
		line[1] = v[1] / n;
		line[2] = v[2] / n;
		line[3] = x0;
		line[4] = y0;
		line[5] = z0;
	}

	static double calcDist2D(const Point2d* points, int count, double *_line, double *dist)
	{
		int j;
		double px = _line[2], py = _line[3];
		double nx = _line[1], ny = -_line[0];
		double sum_dist = 0.;

		for (j = 0; j < count; j++)
		{
			double x, y;

			x = points[j].x - px;
			y = points[j].y - py;

			dist[j] = (double)abs(nx * x + ny * y);
			sum_dist += dist[j];
		}

		return sum_dist;
	}

	static double calcDist3D(const Point3f* points, int count, double *_line, double *dist)
	{
		int j;
		double px = _line[3], py = _line[4], pz = _line[5];
		double vx = _line[0], vy = _line[1], vz = _line[2];
		double sum_dist = 0.;

		for (j = 0; j < count; j++)
		{
			double x, y, z;
			double p1, p2, p3;

			x = points[j].x - px;
			y = points[j].y - py;
			z = points[j].z - pz;

			p1 = vy * z - vz * y;
			p2 = vz * x - vx * z;
			p3 = vx * y - vy * x;

			dist[j] = (double)std::sqrt(p1*p1 + p2 * p2 + p3 * p3);
			sum_dist += dist[j];
		}

		return sum_dist;
	}

	static void weightL1(double *d, int count, double *w)
	{
		int i;

		for (i = 0; i < count; i++)
		{
			double t = abs((double)d[i]);
			w[i] = (double)(1. / MAX(t, eps));
		}
	}

	static void weightL12(double *d, int count, double *w)
	{
		int i;

		for (i = 0; i < count; i++)
		{
			w[i] = 1.0f / (double)std::sqrt(1 + (double)(d[i] * d[i] * 0.5));
		}
	}


	static void weightHuber(double *d, int count, double *w, double _c)
	{
		int i;
		const double c = _c <= 0 ? 1.345f : _c;

		for (i = 0; i < count; i++)
		{
			if (d[i] < c)
				w[i] = 1.0f;
			else
				w[i] = c / d[i];
		}
	}


	static void weightFair(double *d, int count, double *w, double _c)
	{
		int i;
		const double c = _c == 0 ? 1 / 1.3998f : 1 / _c;

		for (i = 0; i < count; i++)
		{
			w[i] = 1 / (1 + d[i] * c);
		}
	}

	static void weightWelsch(double *d, int count, double *w, double _c)
	{
		int i;
		const double c = _c == 0 ? 1 / 2.9846f : 1 / _c;

		for (i = 0; i < count; i++)
		{
			w[i] = (double)std::exp(-d[i] * d[i] * c * c);
		}
	}


	/* Takes an array of 2D points, type of distance (including user-defined
	 distance specified by callbacks, fills the array of four doubles with line
	 parameters A, B, C, D, where (A, B) is the normalized direction vector,
	 (C, D) is the point that belongs to the line. */

	static void fitLine2D(const Point2d * points, int count, int dist,
		double _param, double reps, double aeps, double *line)
	{
		double EPS = count * FLT_EPSILON;
		void(*calc_weights) (double *, int, double *) = 0;
		void(*calc_weights_param) (double *, int, double *, double) = 0;
		int i, j, k;
		double _line[6], _lineprev[6];
		double rdelta = reps != 0 ? reps : 1.0f;
		double adelta = aeps != 0 ? aeps : 0.01f;
		double min_err = DBL_MAX, err = 0;
		RNG rng((uint64)-1);

		memset(line, 0, 4 * sizeof(line[0]));

		switch (dist)
		{
		case CV_DIST_L2:
			return fitLine2D_wods(points, count, 0, line);

		case CV_DIST_L1:
			calc_weights = weightL1;
			break;

		case CV_DIST_L12:
			calc_weights = weightL12;
			break;

		case CV_DIST_FAIR:
			calc_weights_param = weightFair;
			break;

		case CV_DIST_WELSCH:
			calc_weights_param = weightWelsch;
			break;

		case CV_DIST_HUBER:
			calc_weights_param = weightHuber;
			break;

			/*case DIST_USER:
			 calc_weights = (void ( * )(double *, int, double *)) _PFP.fp;
			 break;*/
		default:
			CV_Error(CV_StsBadArg, "Unknown distance type");
		}

		AutoBuffer<double> wr(count * 2);
		double *w = wr, *r = w + count;

		for (k = 0; k < 20; k++)
		{
			int first = 1;
			for (i = 0; i < count; i++)
				w[i] = 0.f;

			for (i = 0; i < MIN(count, 10); )
			{
				j = rng.uniform(0, count);
				if (w[j] < FLT_EPSILON)
				{
					w[j] = 1.f;
					i++;
				}
			}

			fitLine2D_wods(points, count, w, _line);
			for (i = 0; i < 30; i++)
			{
				double sum_w = 0;

				if (first)
				{
					first = 0;
				}
				else
				{
					double t = _line[0] * _lineprev[0] + _line[1] * _lineprev[1];
					t = MAX(t, -1.);
					t = MIN(t, 1.);
					if (abs(acos(t)) < adelta)
					{
						double x, y, d;

						x = (double)abs(_line[2] - _lineprev[2]);
						y = (double)abs(_line[3] - _lineprev[3]);

						d = x > y ? x : y;
						if (d < rdelta)
							break;
					}
				}
				/* calculate distances */
				err = calcDist2D(points, count, _line, r);
				if (err < EPS)
					break;

				/* calculate weights */
				if (calc_weights)
					calc_weights(r, count, w);
				else
					calc_weights_param(r, count, w, _param);

				for (j = 0; j < count; j++)
					sum_w += w[j];

				if (abs(sum_w) > FLT_EPSILON)
				{
					sum_w = 1. / sum_w;
					for (j = 0; j < count; j++)
						w[j] = (double)(w[j] * sum_w);
				}
				else
				{
					for (j = 0; j < count; j++)
						w[j] = 1.f;
				}

				/* save the line parameters */
				memcpy(_lineprev, _line, 4 * sizeof(double));

				/* Run again... */
				fitLine2D_wods(points, count, w, _line);
			}

			if (err < min_err)
			{
				min_err = err;
				memcpy(line, _line, 4 * sizeof(line[0]));
				if (err < EPS)
					break;
			}
		}
	}


	/* Takes an array of 3D points, type of distance (including user-defined
	 distance specified by callbacks, fills the array of four doubles with line
	 parameters A, B, C, D, E, F, where (A, B, C) is the normalized direction vector,
	 (D, E, F) is the point that belongs to the line. */
	static void fitLine3D(Point3f * points, int count, int dist,
		double _param, double reps, double aeps, double *line)
	{
		double EPS = count * FLT_EPSILON;
		void(*calc_weights) (double *, int, double *) = 0;
		void(*calc_weights_param) (double *, int, double *, double) = 0;
		int i, j, k;
		double _line[6] = { 0,0,0,0,0,0 }, _lineprev[6] = { 0,0,0,0,0,0 };
		double rdelta = reps != 0 ? reps : 1.0f;
		double adelta = aeps != 0 ? aeps : 0.01f;
		double min_err = DBL_MAX, err = 0;
		RNG rng((uint64)-1);

		switch (dist)
		{
		case CV_DIST_L2:
			return fitLine3D_wods(points, count, 0, line);

		case CV_DIST_L1:
			calc_weights = weightL1;
			break;

		case CV_DIST_L12:
			calc_weights = weightL12;
			break;

		case CV_DIST_FAIR:
			calc_weights_param = weightFair;
			break;

		case CV_DIST_WELSCH:
			calc_weights_param = weightWelsch;
			break;

		case CV_DIST_HUBER:
			calc_weights_param = weightHuber;
			break;

		default:
			CV_Error(CV_StsBadArg, "Unknown distance");
		}

		AutoBuffer<double> buf(count * 2);
		double *w = buf, *r = w + count;

		for (k = 0; k < 20; k++)
		{
			int first = 1;
			for (i = 0; i < count; i++)
				w[i] = 0.f;

			for (i = 0; i < MIN(count, 10); )
			{
				j = rng.uniform(0, count);
				if (w[j] < FLT_EPSILON)
				{
					w[j] = 1.f;
					i++;
				}
			}

			fitLine3D_wods(points, count, w, _line);
			for (i = 0; i < 30; i++)
			{
				double sum_w = 0;

				if (first)
				{
					first = 0;
				}
				else
				{
					double t = _line[0] * _lineprev[0] + _line[1] * _lineprev[1] + _line[2] * _lineprev[2];
					t = MAX(t, -1.);
					t = MIN(t, 1.);
					if (abs(acos(t)) < adelta)
					{
						double x, y, z, ax, ay, az, dx, dy, dz, d;

						x = _line[3] - _lineprev[3];
						y = _line[4] - _lineprev[4];
						z = _line[5] - _lineprev[5];
						ax = _line[0] - _lineprev[0];
						ay = _line[1] - _lineprev[1];
						az = _line[2] - _lineprev[2];
						dx = (double)abs(y * az - z * ay);
						dy = (double)abs(z * ax - x * az);
						dz = (double)abs(x * ay - y * ax);

						d = dx > dy ? (dx > dz ? dx : dz) : (dy > dz ? dy : dz);
						if (d < rdelta)
							break;
					}
				}
				/* calculate distances */
				err = calcDist3D(points, count, _line, r);
				//if( err < FLT_EPSILON*count )
				//    break;

				/* calculate weights */
				if (calc_weights)
					calc_weights(r, count, w);
				else
					calc_weights_param(r, count, w, _param);

				for (j = 0; j < count; j++)
					sum_w += w[j];

				if (abs(sum_w) > FLT_EPSILON)
				{
					sum_w = 1. / sum_w;
					for (j = 0; j < count; j++)
						w[j] = (double)(w[j] * sum_w);
				}
				else
				{
					for (j = 0; j < count; j++)
						w[j] = 1.f;
				}

				/* save the line parameters */
				memcpy(_lineprev, _line, 6 * sizeof(double));

				/* Run again... */
				fitLine3D_wods(points, count, w, _line);
			}

			if (err < min_err)
			{
				min_err = err;
				memcpy(line, _line, 6 * sizeof(line[0]));
				if (err < EPS)
					break;
			}
		}
	}

}

//==================================fitline直线拟合参数说明========================================
//  points, // 二维点的数组 或者  vector  或者  Mat
//	line, // 输出直线,Vec4f (2d)或Vec6f (3d)的vector （一个是方向向量，另一个是拟合直线上的点）
//	distType, // 距离类型(共7种直线拟合的算法，CV_DIST_L2(最小二乘法)受噪声的影响很大,其他方法具有一定的抗干扰性。
//     1）CV_DIST_L1     =  1,    distance = |x1-x2| + |y1-y2|
//     2）CV_DIST_L2     =  2,    the simple euclidean distance
//     3）CV_DIST_L12    =  4,    L1-L2 metric: distance = 2(sqrt(1+x*x/2) - 1))
//     4）CV_DIST_FAIR   =  5,    distance = c^2(|x|/c-log(1+|x|/c)),    c = 1.3998
//	   5）CV_DIST_WELSCH =  6,    distance = c^2/2(1-exp(-(x/c)^2)),     c = 2.9846
//	   6）CV_DIST_HUBER  =  7     distance = |x|<c ? x^2/2 : c(|x|-c/2), c=1.345

//	param, // 距离参数（c）,跟所选的距离类型有关，值可以设置为0，fitLine()函数本身会自动选择最优化的值
//	reps, // 径向的精度参数  一般设置为 1e-2
//	aeps // 角度精度参数,   一般设置为 1e-2
//==============================================================================================
void cv_DM::fitLine(InputArray _points, OutputArray _line, int distType,
		double param, double reps, double aeps)
{
	Mat points = _points.getMat();

	double linebuf[6] = { 0.f };
	int npoints2 = points.checkVector(2, -1, false);
	int npoints3 = points.checkVector(3, -1, false);

	CV_Assert(npoints2 >= 0 || npoints3 >= 0);

	if (points.depth() != CV_64F || !points.isContinuous())
	{
		Mat temp;
		points.convertTo(temp, CV_64F);
		points = temp;
	}

	if (npoints2 >= 0)
		cv_DM::fitLine2D(points.ptr<Point2d>(), npoints2, distType,
		(double)param, (double)reps, (double)aeps, linebuf);
	else
		cv_DM::fitLine3D(points.ptr<Point3f>(), npoints3, distType,
		(double)param, (double)reps, (double)aeps, linebuf);

	Mat(npoints2 >= 0 ? 4 : 6, 1, CV_64F, linebuf).copyTo(_line);
}


RotatedRect cv_DM::fitEllipse(InputArray _points)
{
	Mat points = _points.getMat();
	int i, n = points.checkVector(2);
	int depth = points.depth();
	//CV_Assert(n >= 0 && (depth == CV_64F));
	CV_Assert(n >= 0 && (depth == CV_32F || depth == CV_32S || depth == CV_64F));
	RotatedRect box;

	if (n < 5)
		CV_Error(CV_StsBadSize, "There should be at least 5 points to fit the ellipse");

	// New fitellipse algorithm, contributed by Dr. Daniel Weiss
	Point2d c(0, 0);
	double gfp[5] = { 0 }, rp[5] = { 0 }, t;
	const double min_eps = 1e-8;
	bool is_double = depth == CV_64F;
	const Point* ptsi = points.ptr<Point>();
	const Point2d* ptsf = points.ptr<Point2d>();

	AutoBuffer<double> _Ad(n * 5), _bd(n);
	double *Ad = _Ad, *bd = _bd;

	// first fit for parameters A - E
	Mat A(n, 5, CV_64F, Ad);
	Mat b(n, 1, CV_64F, bd);
	Mat x(5, 1, CV_64F, gfp);

	for (i = 0; i < n; i++)
	{
		Point2d p = is_double ? ptsf[i] : Point2d((double)ptsi[i].x, (double)ptsi[i].y);
		c += p;
	}
	c.x /= n;
	c.y /= n;

	for (i = 0; i < n; i++)
	{
		Point2d p = is_double ? ptsf[i] : Point2d((double)ptsi[i].x, (double)ptsi[i].y);
		p -= c;

		bd[i] = 10000.0; // 1.0?
		Ad[i * 5] = -(double)p.x * p.x; // A - C signs inverted as proposed by APP
		Ad[i * 5 + 1] = -(double)p.y * p.y;
		Ad[i * 5 + 2] = -(double)p.x * p.y;
		Ad[i * 5 + 3] = p.x;
		Ad[i * 5 + 4] = p.y;
	}

	solve(A, b, x, DECOMP_SVD);

	// now use general-form parameters A - E to find the ellipse center:
	// differentiate general form wrt x/y to get two equations for cx and cy
	A = Mat(2, 2, CV_64F, Ad);
	b = Mat(2, 1, CV_64F, bd);
	x = Mat(2, 1, CV_64F, rp);
	Ad[0] = 2 * gfp[0];
	Ad[1] = Ad[2] = gfp[2];
	Ad[3] = 2 * gfp[1];
	bd[0] = gfp[3];
	bd[1] = gfp[4];
	solve(A, b, x, DECOMP_SVD);

	// re-fit for parameters A - C with those center coordinates
	A = Mat(n, 3, CV_64F, Ad);
	b = Mat(n, 1, CV_64F, bd);
	x = Mat(3, 1, CV_64F, gfp);
	for (i = 0; i < n; i++)
	{
		Point2d p = is_double ? ptsf[i] : Point2d((double)ptsi[i].x, (double)ptsi[i].y);
		p -= c;
		bd[i] = 1.0;
		Ad[i * 3] = (p.x - rp[0]) * (p.x - rp[0]);
		Ad[i * 3 + 1] = (p.y - rp[1]) * (p.y - rp[1]);
		Ad[i * 3 + 2] = (p.x - rp[0]) * (p.y - rp[1]);
	}
	solve(A, b, x, DECOMP_SVD);

	// store angle and radii
	rp[4] = -0.5 * atan2(gfp[2], gfp[1] - gfp[0]); // convert from APP angle usage
	if (abs(gfp[2]) > min_eps)
		t = gfp[2] / sin(-2.0 * rp[4]);
	else // ellipse is rotated by an integer multiple of pi/2
		t = gfp[1] - gfp[0];
	rp[2] = abs(gfp[0] + gfp[1] - t);
	if (rp[2] > min_eps)
		rp[2] = std::sqrt(2.0 / rp[2]);
	rp[3] = abs(gfp[0] + gfp[1] + t);
	if (rp[3] > min_eps)
		rp[3] = std::sqrt(2.0 / rp[3]);

	box.center.x = (double)rp[0] + c.x;
	box.center.y = (double)rp[1] + c.y;
	box.size.width = (double)(rp[2] * 2);
	box.size.height = (double)(rp[3] * 2);
	if (box.size.width > box.size.height)
	{
		double tmp;
		CV_SWAP(box.size.width, box.size.height, tmp);
		box.angle = (double)(90 + rp[4] * 180 / CV_PI);
	}
	if (box.angle < -180)
		box.angle += 360;
	if (box.angle > 360)
		box.angle -= 360;

	return box;
}





Mat translateImage(Mat& src, int xOffset, int yOffset, bool bScale)
{
	int src_cols = src.cols;
	int src_rows = src.rows;
	int dst_cols = 0;
	int dst_rows = 0;
	cv::Rect rectSrc, rectRet;
	if(bScale)
	{
		dst_cols = src_cols + abs(xOffset);
		dst_rows = src_rows + abs(yOffset);
		rectSrc.x = 0;
		rectSrc.y = 0;
		rectSrc.width = src_cols;
		rectSrc.height = src_rows;
	}
	else
	{
		dst_cols = src.cols;
		dst_rows = src.rows;

		if (xOffset >= 0)
		{
			rectSrc.x = 0;
		}
		else
		{
			rectSrc.x = abs(xOffset);
		}
		if (yOffset >= 0)
		{
			rectSrc.y = 0;
		}
		else
		{
			rectSrc.y = abs(yOffset);
		}
		rectSrc.width = src_cols - abs(xOffset);
		rectSrc.height = src_rows - abs(yOffset);
	}
	// 修正输出的ROI
	if (xOffset >= 0)
	{
		rectRet.x = xOffset;
	}
	else
	{
		rectRet.x = 0;
	}
	if (yOffset >= 0)
	{
		rectRet.y = yOffset;
	}
	else
	{
		rectRet.y = 0;
	}
	rectRet.width = rectSrc.width;
	rectRet.height = rectSrc.height;
	// 复制图像
	Mat matRet(dst_rows, dst_cols, src.type(), Scalar(255));
	src(rectSrc).copyTo(matRet(rectRet));
	return matRet;
}
