#ifndef RTT_LINUX_PREFERENCES_DIALOG_H
#define RTT_LINUX_PREFERENCES_DIALOG_H

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/statline.h>
#include <wx/activityindicator.h>
#include <string>

#pragma once

namespace Rtt
{
	class NewPreferencesDialog : public wxDialog
	{
	public:
		NewPreferencesDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);

	private:
		void SetProperties();
		void SetLayout();

	protected:
		wxCheckBox *showRuntimeErrors;
		wxCheckBox *automaticallyLaunchLastProject;
		wxStaticText *relaunchSimulatorOptionText;
		wxRadioButton *relaunchOnModifyAlways;
		wxRadioButton *relaunchOnModifyNever;
		wxRadioButton *relaunchOnModifyAskEveryTime;
		wxButton *btnOK;
		wxButton *btnCancel;

		DECLARE_EVENT_TABLE();

	public:
		void OnOKClicked(wxCommandEvent &event);
		void OnCancelClicked(wxCommandEvent &event);
	};

} // namespace Rtt

#endif // RTT_LINUX_PREFERENCES_DIALOG_H
