#ifndef DM_DIALOG_H
#define DM_DIALOG_H

#include <QString>
#include <QWidget>
#include <QDir>

class DM_Dialog
{
public:
    enum DM_DialogType
    {

        DM_DialogType_Default = -1,//默认模式
        DM_DialogType_Delete = 1,//删除模式
        DM_DialogType_Load,//加载模式
        DM_DialogType_New,//新建模式
    };
    public:
        static bool getProjectName(QString& name, QWidget *parent = 0, const QString& title = "");
        static bool getOpenProjectName(QString& name, QWidget *parent = 0, const QString& title = "",
                                       const QString &path = QString(), QDir::Filters filter = QDir::NoFilter,
                                       DM_DialogType type = DM_DialogType_Default);
//		static int getActivate(QWidget *parent = 0);
    private:
        explicit DM_Dialog(){}
        ~DM_Dialog(){}
};

#endif // DM_DIALOG_H
