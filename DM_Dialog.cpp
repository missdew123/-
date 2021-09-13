#include "DM_Dialog.h"

#include "Dialog_GetProjectName.h"
#include "Dialog_GetOpenProjectName.h"
//#include "Dialog_Activate.h"



bool DM_Dialog::getProjectName(QString& name, QWidget* parent, const QString& title)
{
    Dialog_GetProjectName* dialog = new Dialog_GetProjectName(parent, title);
    dialog->exec();
    bool isOK = dialog->getText(name);
    delete dialog;
    return isOK;
}

bool DM_Dialog::getOpenProjectName(QString& name, QWidget* parent, const QString& title,
                                   const QString& path, QDir::Filters filter, DM_DialogType type)
{
    Dialog_GetOpenProjectName* dialog = new Dialog_GetOpenProjectName(parent, title, path, filter);
    if(type == DM_DialogType_Delete)//删除模式
    {
        dialog->setDeleteMode();
    }
    else if(type == DM_DialogType_Load)//加载模式
    {
        dialog->setLoadMode();
    }
    else if(type == DM_DialogType_New)//新建模式
    {
        dialog->setNewMode();
    }

    dialog->exec();
    bool isOK = dialog->getOpenName(name);
    delete dialog;
    return isOK;
}

//int DM_Dialog::getActivate(QWidget* parent)
//{
//	Dialog_Activate* dialog = new Dialog_Activate(parent);
//	dialog->exec();
//	int status = dialog->getStatus();
//	delete dialog;
//	return status;
//}

