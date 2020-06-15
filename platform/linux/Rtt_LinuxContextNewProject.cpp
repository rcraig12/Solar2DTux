#include <pwd.h>
#include <libgen.h>
#include <string.h>
#include "Core/Rtt_Build.h"
#include "Core/Rtt_Time.h"
#include "Rtt_Runtime.h"
#include "Rtt_LuaContext.h"
#include "Core/Rtt_Types.h"
#include "Rtt_LinuxContext.h"
#include "Rtt_LinuxPlatform.h"
#include "Rtt_LinuxRuntimeDelegate.h"
#include "Rtt_LuaFile.h"
#include "Core/Rtt_FileSystem.h"
#include "Rtt_Archive.h"
#include "Display/Rtt_Display.h"
#include "Display/Rtt_DisplayDefaults.h"
#include "Rtt_KeyName.h"
#include "Rtt_Freetype.h"
#include "Rtt_LuaLibSimulator.h"
#include "Rtt_LinuxSimulatorView.h"
#include "Rtt_LinuxContextNewProject.h"

// Eport for LUA
Rtt_EXPORT int luaopen_lfs(lua_State *L);

using namespace std;
using namespace Rtt;

namespace Rtt
{
	NewProjectDialog::NewProjectDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
		wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE),
			fProjectName(""),
			fTemplateName(""),
			fScreenWidth(320),
			fScreenHeight(480),
			fOrientationIndex(""),
			fProjectPath(""),
			fProjectSavePath(""),
			fResourcePath("")
			
	{
		SetSize(wxSize(600, 425));
		txtApplicationName = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
		txtProjectFolder = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
		btnBrowse = new wxButton(this, wxID_OPEN, wxT("&Browse..."));
		rProjectOption1 = new wxRadioButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
		rProjectOption2 = new wxRadioButton(this, wxID_ANY, wxEmptyString);
		rProjectOption3 = new wxRadioButton(this, wxID_ANY, wxEmptyString);
		rProjectOption4 = new wxRadioButton(this, wxID_ANY, wxEmptyString);
		const wxString cboScreenSizePreset_choices[] = {
			wxT("Phone Preset"),
			wxT("Tablet Preset"),
			wxT("Custom"),
		};
		cboScreenSizePreset = new wxComboBox(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, 3, cboScreenSizePreset_choices, wxCB_DROPDOWN);
		txtWidth = new wxTextCtrl(this, wxID_ANY, to_string(fScreenWidth));
		txtHeight = new wxTextCtrl(this, wxID_ANY, to_string(fScreenHeight));
		rUpright = new wxRadioButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
		rSideways = new wxRadioButton(this, wxID_ANY, wxEmptyString);
		btnOK = new wxButton(this, wxID_OK, wxT("OK"));
		btnCancel = new wxButton(this, wxID_CANCEL, wxT("Cancel"));

		SetProperties();
		DoLayout();
	}

	void NewProjectDialog::SetProperties()
	{
		SetTitle(wxT("New Project"));
		SetSize(wxSize(600, 425));
		SetFont(wxFont(8, wxDEFAULT, wxNORMAL, wxNORMAL, 0, wxT("")));
		txtApplicationName->SetValue("Untitled");
		txtProjectFolder->Enable(false);
		cboScreenSizePreset->SetSelection(0);
		txtWidth->Enable(false);
		txtHeight->Enable(false);
		btnOK->SetDefault();
		this->SetProjectPath();
		this->SetResourcePath();
	}

	void NewProjectDialog::DoLayout()
	{
		wxBoxSizer* dialogLayout = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* dialogTop = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* dialogMiddle = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* dialogBottom = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* dialogButtons = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* groupBoxRight = new wxBoxSizer(wxVERTICAL);
		wxStaticBoxSizer* groupBoxLeft = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Project Template")), wxVERTICAL);
		wxStaticBoxSizer* groupBoxRightBottom = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Default Orientation")), wxHORIZONTAL);
		wxStaticBoxSizer* groupBoxRightTop = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Upright Screen Size")), wxVERTICAL);
		wxBoxSizer* topColumn1 = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* topColumn2 = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* topColumn3 = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* topRow1 = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* topRow2 = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* topRow3 = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* topRow4 = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* middleRightTopColumn1 = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* middleRightTopColumn2 = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* middleRightBottomColumn1 = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer* middleRightBottomColumn2 = new wxBoxSizer(wxHORIZONTAL);
		wxStaticText* appNameText = new wxStaticText(this, wxID_ANY, wxT("Application Name : "));
		wxStaticText* projectFolderText = new wxStaticText(this, wxID_ANY, wxT("Project Folder : "));
		wxStaticText* blankProjectText = new wxStaticText(this, wxID_ANY, wxT("Blank\nCreates a project folder with an empty \"main.lua\""));
		wxStaticText* tabBarProjecText = new wxStaticText(this, wxID_ANY, wxT("Tab Bar Application\nMultiscreen application using a Tab Bar for"));
		wxStaticText* physicsProjectText = new wxStaticText(this, wxID_ANY, wxT("Physics Based Game\nApplication using the physics and composer"));
		wxStaticText* eBookText = new wxStaticText(this, wxID_ANY, wxT("eBook\nMulti-page interface using the composer"));
		wxStaticText* widthText = new wxStaticText(this, wxID_ANY, wxT("Width : "), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
		wxStaticText* heightText = new wxStaticText(this, wxID_ANY, wxT("Height : "), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
		wxStaticText* orientationText1 = new wxStaticText(this, wxID_ANY, wxT("Upright"));
		wxStaticText* orientationText2 = new wxStaticText(this, wxID_ANY, wxT("Sideways"));
		wxStaticLine* staticLineSeparator = new wxStaticLine(this, wxID_ANY);

		// set fonts
		appNameText->SetFont(wxFont(8, wxDEFAULT, wxNORMAL, wxNORMAL, 0, wxT("")));
		projectFolderText->SetFont(wxFont(8, wxDEFAULT, wxNORMAL, wxNORMAL, 0, wxT("")));

		// add to top columns
		topColumn1->Add(appNameText, 0, wxALIGN_RIGHT | wxBOTTOM | wxTOP, 6);
		topColumn1->Add(projectFolderText, 0, wxALIGN_RIGHT | wxBOTTOM | wxTOP, 6);
		topColumn2->Add(txtApplicationName, 0, wxEXPAND, 0);
		topColumn2->Add(txtProjectFolder, 0, wxEXPAND, 0);
		topColumn3->Add(20, 16, 0, wxBOTTOM | wxTOP, 6);
		topColumn3->Add(btnBrowse, 0, 0, 0);

		// add to top rows
		topRow1->Add(rProjectOption1, 0, 0, 0);
		topRow1->Add(blankProjectText, 0, 0, 0);
		topRow2->Add(rProjectOption2, 0, 0, 0);
		topRow2->Add(tabBarProjecText, 0, 0, 0);
		topRow3->Add(rProjectOption3, 0, 0, 0);
		topRow3->Add(physicsProjectText, 0, 0, 0);
		topRow4->Add(rProjectOption4, 0, 0, 0);
		topRow4->Add(eBookText, 0, 0, 0);
		middleRightTopColumn1->Add(widthText, 1, wxBOTTOM | wxTOP, 7);
		middleRightTopColumn1->Add(txtWidth, 0, 0, 0);
		middleRightTopColumn2->Add(heightText, 1, wxBOTTOM | wxTOP, 7);
		middleRightTopColumn2->Add(txtHeight, 0, 0, 0);
		middleRightBottomColumn1->Add(rUpright, 0, 0, 0);
		middleRightBottomColumn1->Add(orientationText1, 0, 0, 0);
		middleRightBottomColumn2->Add(rSideways, 0, 0, 0);
		middleRightBottomColumn2->Add(orientationText2, 0, 0, 0);

		// add to groupboxes
		groupBoxLeft->Add(topRow1, 1, wxEXPAND | wxRIGHT | wxTOP, 7);
		groupBoxLeft->Add(topRow2, 1, wxEXPAND, 0);
		groupBoxLeft->Add(topRow3, 1, wxEXPAND, 0);
		groupBoxLeft->Add(topRow4, 1, wxEXPAND, 0);
		groupBoxRight->Add(groupBoxRightTop, 1, wxBOTTOM | wxEXPAND, 7);
		groupBoxRight->Add(groupBoxRightBottom, 0, wxEXPAND, 0);
		groupBoxRight->Add(20, 20, 1, wxEXPAND, 0);
		groupBoxRightTop->Add(cboScreenSizePreset, 0, wxALL | wxEXPAND, 7);
		groupBoxRightTop->Add(middleRightTopColumn1, 0, wxEXPAND | wxRIGHT, 7);
		groupBoxRightTop->Add(middleRightTopColumn2, 0, wxBOTTOM | wxEXPAND | wxRIGHT, 7);
		groupBoxRightBottom->Add(middleRightBottomColumn1, 1, wxBOTTOM | wxEXPAND | wxTOP, 7);
		groupBoxRightBottom->Add(middleRightBottomColumn2, 1, wxBOTTOM | wxEXPAND | wxTOP, 7);

		// add to dialog buttons
		dialogButtons->Add(btnOK, 0, wxRIGHT, 5);
		dialogButtons->Add(btnCancel, 0, 0, 0);

		// add to dialog layouts
		dialogTop->Add(topColumn1, 0, wxLEFT | wxRIGHT, 7);
		dialogTop->Add(topColumn2, 1, wxEXPAND, 0);
		dialogTop->Add(topColumn3, 0, wxEXPAND | wxLEFT | wxRIGHT, 7);
		dialogMiddle->Add(groupBoxLeft, 1, wxEXPAND | wxLEFT, 7);
		dialogMiddle->Add(groupBoxRight, 1, wxEXPAND | wxLEFT | wxRIGHT, 7);
		dialogBottom->Add(staticLineSeparator, 0, wxEXPAND | wxLEFT | wxRIGHT, 7);
		dialogBottom->Add(dialogButtons, 1, wxALIGN_RIGHT | wxALL, 7);
		dialogLayout->Add(dialogTop, 0, wxBOTTOM | wxEXPAND | wxTOP, 8);
		dialogLayout->Add(dialogMiddle, 1, wxBOTTOM | wxEXPAND | wxTOP, 7);
		dialogLayout->Add(dialogBottom, 0, wxEXPAND, 0);

		SetSizer(dialogLayout);
		Layout();
	}
	
	BEGIN_EVENT_TABLE(NewProjectDialog, wxDialog)
		EVT_COMBOBOX(wxID_ANY, NewProjectDialog::OnChange)
		EVT_BUTTON(wxID_OPEN, NewProjectDialog::OnProjectFolderBrowse)
		EVT_BUTTON(wxID_OK, NewProjectDialog::OnOKClicked)
		EVT_BUTTON(wxID_CANCEL, NewProjectDialog::OnCancelClicked)
	END_EVENT_TABLE();

	void NewProjectDialog::OnProjectFolderBrowse(wxCommandEvent &event)
	{
		event.Skip();
		wxDirDialog openDirDialog(this, _("Choose Project Directory"), fProjectPath, 0, wxDefaultPosition);

		if (openDirDialog.ShowModal() == wxID_OK)
		{ 
			fProjectPath = string(openDirDialog.GetPath());
			txtProjectFolder->SetValue(fProjectPath);
		} 
		else if (openDirDialog.ShowModal() == wxID_CANCEL)
		{	
			return;	
		}
	}

	void NewProjectDialog::OnChange(wxCommandEvent &event)
	{
		event.Skip();
		wxString strPreset = cboScreenSizePreset->GetValue();
		
		if (strcmp(strPreset, "Phone Preset") == 0)
		{
			fScreenWidth = 320;
			fScreenHeight = 480;
			txtWidth->Enable(false);
			txtHeight->Enable(false);
			wxLogDebug("Preset is Phone Preset" );
		}
		else if (strcmp(strPreset, "Tablet Preset") == 0)
		{
			fScreenWidth = 768;
			fScreenHeight = 1024;
			txtWidth->Enable(false);
			txtHeight->Enable(false);
			wxLogDebug("Preset is Tablet Preset" );
		}
		else if (strcmp(strPreset, "Custom") == 0)
		{
			txtWidth->Enable(true);
			txtHeight->Enable(true);
			wxLogDebug("Preset is Custom Preset" );
		}
		
		txtWidth->SetValue(to_string(fScreenWidth));
		txtHeight->SetValue(to_string(fScreenHeight));
	}

	void NewProjectDialog::OnOKClicked(wxCommandEvent &event)
	{
		wxLogDebug("fProjectName = %s " , txtApplicationName->GetValue().ToStdString());
		bool bDialogClean = true;
		
		// Determine the application template we are using
		if (rProjectOption1->GetValue() == true)
		{
			fTemplateName = "blank";
			//wxLogDebug(wxT("Project = blank\n" ));
		}
		
		if (rProjectOption2->GetValue() == true)
		{
			fTemplateName = "app";
			//wxLogDebug(wxT("Project = app\n" ));
		}
		
		if (rProjectOption3->GetValue() == true)
		{
			fTemplateName = "game";
			//wxLogDebug(wxT("Project = game\n" ));
		}
		
		if (rProjectOption4->GetValue() == true)
		{
			fTemplateName = "ebook";
			//wxLogDebug(wxT("Project = ebook\n" ));
		}
		
		fScreenWidth = wxAtoi(txtWidth->GetValue());
		fScreenHeight = wxAtoi(txtHeight->GetValue());
		
		if (fScreenWidth == 0 || fScreenHeight == 0)
		{
			wxMessageBox(wxT("Height and Width values must be numeric and larger that 0"), wxT("Screen Dimension Errors"), wxICON_INFORMATION);
			bDialogClean = false;
		}
		
		wxLogDebug("dimension width x height = %s x %s" , to_string(fScreenWidth), to_string(fScreenHeight));

		if (rUpright->GetValue() == true)
		{
			fOrientationIndex = "portait";
			//wxLogDebug(wxT("Orientation = portrait\n" ));
		}		
		
		if (rSideways->GetValue() == true)
		{
			fOrientationIndex = "landscapeRight";
			//wxLogDebug(wxT("Orientation = landscapeRight\n" ));
		}		
		
		// TODO: Make sure all variables are sane values before running project creation process
		string fProjectSavePath(txtProjectFolder->GetValue().ToStdString());
	    fProjectName = txtApplicationName->GetValue().ToStdString();
		fProjectSavePath.append("/");
		fProjectSavePath.append(fProjectName);

		wxLogDebug("fProjectSavePath = %s ", fProjectSavePath);
		
		//check if project folder already exists and that the height and width are numbers
		if (Rtt_IsDirectory(fProjectSavePath.c_str()) == true)
		{
			wxMessageBox( wxT("Project of that name already exists."), wxT("Duplicate Project Name"), wxICON_INFORMATION);
			bDialogClean = false;
		} 
		
		if (bDialogClean == true)
		{
			this->CreateProject(fProjectSavePath);
			EndModal(wxID_OK);
		}
	}

	void NewProjectDialog::OnCancelClicked(wxCommandEvent &event)
	{
		EndModal(wxID_CLOSE);
	}
	
	void NewProjectDialog::SetProjectPath()
	{
		struct passwd* pw = getpwuid(getuid());
		const char* homedir = pw->pw_dir;
		fProjectPath = string(homedir);
		fProjectPath.append("/Documents/Solar2D Projects");
		txtProjectFolder->SetValue(fProjectPath);
	}

	void NewProjectDialog::SetResourcePath()
	{
		static char buf[ PATH_MAX + 1];
		ssize_t count = readlink("/proc/self/exe", buf, PATH_MAX);
		const char *appPath;
		
		if (count != -1)
		{
			appPath = dirname(buf);
		}

		fResourcePath = string(appPath);
		fResourcePath.append("/Resources");
		wxLogDebug("appPath = %s\n", string(appPath));
	}
	
	void NewProjectDialog::CreateProject(string projectFolder)
	{
		string fNewProjectLuaScript = fResourcePath;
		fNewProjectLuaScript.append("/homescreen/newproject.lua");
		wxLogDebug("fNewProjectLuaScript = %s\n", string(fNewProjectLuaScript));
		
		string fTemplatesDir(fResourcePath);
		fTemplatesDir.append("/homescreen/templates");
		wxLogDebug("fTemplatesDir = %s\n", string(fTemplatesDir));
		
		if (Rtt_IsDirectory(projectFolder.c_str()) == false)
		{
			Rtt_MakeDirectory(projectFolder.c_str());
			wxLogDebug("Creating directory = %s\n", projectFolder);
		}

		lua_State *L = luaL_newstate();
		luaL_openlibs(L);
		Rtt::LuaContext::RegisterModuleLoader(L, "lfs", luaopen_lfs);

		const char *script = fNewProjectLuaScript.c_str();
		int status = luaL_loadfile(L ,script); 
		Rtt_ASSERT(0 == status);

		lua_createtable(L, 0, 6);
		{
			lua_pushboolean(L, true);
			lua_setfield(L, -2, "isSimulator");

			lua_pushstring(L, fTemplateName.c_str());
			lua_setfield(L, -2, "template");

			lua_pushinteger(L, fScreenWidth);
			lua_setfield(L, -2, "width");

			lua_pushinteger(L, fScreenHeight);
			lua_setfield(L, -2, "height");

			lua_pushstring(L, 0 == fOrientationIndex ? "portrait" : "landscapeRight");
			lua_setfield(L, -2, "orientation");

			lua_pushstring(L, projectFolder.c_str());
			lua_setfield(L, -2, "savePath");

			lua_pushstring(L, fTemplatesDir.c_str());
			lua_setfield(L, -2, "templateBaseDir");
		}

		status = Rtt::LuaContext::DoCall(L, 1, 0); 
		Rtt_ASSERT(0 == status);
		lua_close(L);
	}
}
