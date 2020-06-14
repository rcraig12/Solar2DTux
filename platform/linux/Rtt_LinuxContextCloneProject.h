#ifndef RTT_LINUX_CONTEXT_CLONE_PROJECT_H
#define RTT_LINUX_CONTEXT_CLONE_PROJECT_H

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/statline.h>
#include <wx/activityindicator.h>
#include <string>

#pragma once

namespace Rtt
{
	class NewCloneDialog : public wxDialog
	{
	public:
		NewCloneDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);

	private:
		void SetProperties();
		void SetLayout();
		void CloneProject();

	protected:
		wxTextCtrl *txtCloneUrl;
		wxTextCtrl *txtProjectFolder;
		wxButton *btnBrowse;
		wxActivityIndicator *activityIndicator;
		wxButton *btnOK;
		wxButton *btnCancel;

		DECLARE_EVENT_TABLE();

	public:
		void OnProjectFolderBrowse(wxCommandEvent &event);
		void OnOKClicked(wxCommandEvent &event);
		void OnCancelClicked(wxCommandEvent &event);
	};

} // namespace Rtt

#endif // RTT_LINUX_CONTEXT_CLONE_PROJECT_H
