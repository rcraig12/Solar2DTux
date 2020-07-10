#include "Rtt_LinuxConsole.h"

#ifndef wxHAS_IMAGES_IN_RESOURCES
	#include "resource/console.xpm"
	#include "resource/save.xpm"
	#include "resource/copy.xpm"
	#include "resource/erase.xpm"
	#include "resource/search-left.xpm"
	#include "resource/search-right.xpm"
	#include "resource/match-case.xpm"
	#include "resource/looping-search.xpm"	
	#include "resource/cog.xpm"
#endif

using namespace std;

Rtt_LinuxConsole::Rtt_LinuxConsole(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE) 
{
	
	SetIcon(console_xpm);		
	
    SetSize(wxSize(1098, 437));
    panelToolBar = new wxPanel(this, wxID_ANY);
    statusbar = CreateStatusBar(1);
	bitmapBtnSave = new wxBitmapButton(panelToolBar, wxID_ANY,  wxIcon(save_xpm), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxBU_AUTODRAW|wxBU_EXACTFIT|wxBU_NOTEXT);
    bitmapBtnCopy = new wxBitmapButton(panelToolBar, wxID_ANY,  wxIcon(copy_xpm), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxBU_AUTODRAW|wxBU_EXACTFIT|wxBU_NOTEXT);
    bitmapBtnErase = new wxBitmapButton(panelToolBar, wxID_ANY,  wxIcon(erase_xpm), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxBU_AUTODRAW|wxBU_EXACTFIT|wxBU_NOTEXT);
    txtFind = new wxTextCtrl(panelToolBar, wxID_ANY, wxEmptyString);
    bitmapBtnFindLeft = new wxBitmapButton(panelToolBar, wxID_ANY,  wxIcon(search_left_xpm), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxBU_AUTODRAW|wxBU_EXACTFIT|wxBU_NOTEXT);
    bitmapBtnFindRight = new wxBitmapButton(panelToolBar, wxID_ANY,  wxIcon(search_right_xpm), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxBU_AUTODRAW|wxBU_EXACTFIT|wxBU_NOTEXT);
    bitmapBtnMatchCase = new wxBitmapButton(panelToolBar, wxID_ANY,  wxIcon(match_case_xpm), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxBU_AUTODRAW|wxBU_EXACTFIT|wxBU_NOTEXT);
    bitmapBtnLoopingSearch = new wxBitmapButton(panelToolBar, wxID_ANY,  wxIcon(looping_search_xpm), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxBU_AUTODRAW|wxBU_EXACTFIT|wxBU_NOTEXT);
    bitmapBtnMenu = new wxBitmapButton(panelToolBar, wxID_ANY,  wxIcon(cog_xpm), wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxBU_AUTODRAW|wxBU_EXACTFIT|wxBU_NOTEXT);
    txtLog = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTE_MULTILINE|wxTE_RICH2);
	linuxIPCServer = new Rtt_LinuxIPCServer();
	
    SetProperties();
    DoLayout();

}


void Rtt_LinuxConsole::SetProperties()
{
	
	wxInitAllImageHandlers();

	
    SetTitle(wxT("Solar2DTux Simulator Console"));
    int statusbar_widths[] = { -1 };
    statusbar->SetStatusWidths(1, statusbar_widths);

    // statusbar fields
    const wxString statusbar_fields[] = {
        wxT("Errors #0 Alerts #0"),
    };
    for(int i = 0; i < statusbar->GetFieldsCount(); ++i) {
        statusbar->SetStatusText(statusbar_fields[i], i);
    }
	
    bitmapBtnSave->SetBackgroundColour(wxColour(37, 37, 38));
    bitmapBtnSave->SetSize(bitmapBtnSave->GetBestSize());
    bitmapBtnCopy->SetBackgroundColour(wxColour(37, 37, 38));
    bitmapBtnCopy->SetSize(bitmapBtnCopy->GetBestSize());
    bitmapBtnErase->SetBackgroundColour(wxColour(37, 37, 38));
    bitmapBtnErase->SetSize(bitmapBtnErase->GetBestSize());
    txtFind->SetMinSize(wxSize(250, -1));
    txtFind->SetBackgroundColour(wxColour(37, 37, 38));
    txtFind->SetForegroundColour(wxColour(255, 255, 255));
    bitmapBtnFindLeft->SetBackgroundColour(wxColour(37, 37, 38));
    bitmapBtnFindLeft->SetSize(bitmapBtnFindLeft->GetBestSize());
    bitmapBtnFindRight->SetBackgroundColour(wxColour(37, 37, 38));
    bitmapBtnFindRight->SetSize(bitmapBtnFindRight->GetBestSize());
    bitmapBtnMatchCase->SetBackgroundColour(wxColour(37, 37, 38));
    bitmapBtnMatchCase->SetSize(bitmapBtnMatchCase->GetBestSize());
    bitmapBtnLoopingSearch->SetBackgroundColour(wxColour(37, 37, 38));
    bitmapBtnLoopingSearch->SetSize(bitmapBtnLoopingSearch->GetBestSize());
    bitmapBtnMenu->SetBackgroundColour(wxColour(37, 37, 38));
    bitmapBtnMenu->SetSize(bitmapBtnMenu->GetBestSize());
    panelToolBar->SetBackgroundColour(wxColour(37, 37, 38));
    txtLog->SetBackgroundColour(wxColour(0, 0, 0));
    txtLog->SetForegroundColour(wxColour(255, 255, 255));
	statusbar->SetBackgroundColour(wxColour(37, 37, 38));
	statusbar->SetForegroundColour(wxColour(255, 255, 255));
	txtLog->SetFocus();

/*	
	const char * const kind =
#if wxUSE_DDE_FOR_IPC
                 "DDE"
#else
                 "TCP"
#endif
                 ;
*/
    // Create a new server
    if ( !linuxIPCServer->Create(IPC_SERVICE) ){	
    
		//wxLogMessage("%s server failed to start on %s", kind, IPC_SERVICE);
    
	} else {
 
		//wxLogMessage("%s server started on %s", kind, IPC_SERVICE);
	
	}
	
}


void Rtt_LinuxConsole::DoLayout()
{
    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    sizer2->Add(bitmapBtnSave, 0, 0, 0);
    sizer2->Add(bitmapBtnCopy, 0, 0, 0);
    sizer2->Add(bitmapBtnErase, 0, 0, 0);
    wxStaticText* lblFind = new wxStaticText(panelToolBar, wxID_ANY, wxT("Find:"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    lblFind->SetForegroundColour(wxColour(255, 255, 255));
    sizer2->Add(lblFind, 0, wxALIGN_CENTER_VERTICAL, 0);
    sizer2->Add(txtFind, 0, wxALIGN_CENTER_VERTICAL, 0);
    sizer2->Add(bitmapBtnFindLeft, 0, 0, 0);
    sizer2->Add(bitmapBtnFindRight, 0, 0, 0);
    sizer2->Add(bitmapBtnMatchCase, 0, 0, 0);
    sizer2->Add(bitmapBtnLoopingSearch, 0, 0, 0);
    sizer2->Add(bitmapBtnMenu, 0, 0, 0);
    panelToolBar->SetSizer(sizer2);
    sizer1->Add(panelToolBar, 0, wxEXPAND, 0);
    sizer1->Add(txtLog, 1, wxEXPAND, 0);
    SetSizer(sizer1);
    Layout();
	
}

BEGIN_EVENT_TABLE(Rtt_LinuxConsole, wxFrame)
    EVT_BUTTON(wxID_ANY, Rtt_LinuxConsole::OnBtnSaveClick)
    EVT_BUTTON(wxID_ANY, Rtt_LinuxConsole::OnBtnCopyClick)
    EVT_BUTTON(wxID_ANY, Rtt_LinuxConsole::OnBtnEraseClick)
    EVT_BUTTON(wxID_ANY, Rtt_LinuxConsole::OnBtnFindLeftClick)
    EVT_BUTTON(wxID_ANY, Rtt_LinuxConsole::OnBtnFindRightClick)
    EVT_BUTTON(wxID_ANY, Rtt_LinuxConsole::OnBtnMatchCaseClick)
    EVT_BUTTON(wxID_ANY, Rtt_LinuxConsole::OnBtnLoopingSearchClick)
END_EVENT_TABLE();

void Rtt_LinuxConsole::OnBtnSaveClick(wxCommandEvent &event)
{
    event.Skip();
	txtLog->SetFocus();
	
    // notify the user that he hasn't implemented the event handler yet
    wxLogDebug(wxT("Event handler (Rtt_LinuxConsole::onBtnSaveClick) not implemented yet"));
}

void Rtt_LinuxConsole::OnBtnCopyClick(wxCommandEvent &event)
{
    event.Skip();
	txtLog->SetFocus();
    // notify the user that he hasn't implemented the event handler yet
    wxLogDebug(wxT("Event handler (Rtt_LinuxConsole::onBtnCopyClick) not implemented yet"));
}

void Rtt_LinuxConsole::OnBtnEraseClick(wxCommandEvent &event) 
{
    event.Skip();
	txtLog->SetFocus();
    // notify the user that he hasn't implemented the event handler yet
    wxLogDebug(wxT("Event handler (Rtt_LinuxConsole::onBtnEraseClick) not implemented yet"));
}

void Rtt_LinuxConsole::OnBtnFindLeftClick(wxCommandEvent &event) 
{
    event.Skip();
	txtLog->SetFocus();
    // notify the user that he hasn't implemented the event handler yet
    wxLogDebug(wxT("Event handler (Rtt_LinuxConsole::onBtnFindLeftClick) not implemented yet"));
}

void Rtt_LinuxConsole::OnBtnFindRightClick(wxCommandEvent &event)  
{
    event.Skip();
	txtLog->SetFocus();
    // notify the user that he hasn't implemented the event handler yet
    wxLogDebug(wxT("Event handler (Rtt_LinuxConsole::onBtnFindRightClick) not implemented yet"));
}

void Rtt_LinuxConsole::OnBtnMatchCaseClick(wxCommandEvent &event) 
{
    event.Skip();
	txtLog->SetFocus();
    // notify the user that he hasn't implemented the event handler yet
    wxLogDebug(wxT("Event handler (Rtt_LinuxConsole::onBtnMatchCaseClick) not implemented yet"));
}

void Rtt_LinuxConsole::OnBtnLoopingSearchClick(wxCommandEvent &event) 
{
    event.Skip();
	txtLog->SetFocus();
    // notify the user that he hasn't implemented the event handler yet
    wxLogDebug(wxT("Event handler (Rtt_LinuxConsole::onBtnLoopingSearchClick) not implemented yet"));
}

void Rtt_LinuxConsole::UpdateLog(wxString message)
{
	
	txtLog->SetInsertionPointEnd();
	txtLog->SetDefaultStyle(wxTextAttr(*wxWHITE));
	txtLog->AppendText( message );
	
}

void Rtt_LinuxConsole::UpdateLogWarning(wxString message)
{
	
	txtLog->SetInsertionPointEnd();
	txtLog->SetDefaultStyle(wxTextAttr(*wxYELLOW));
	txtLog->AppendText( message  );
	
}

void Rtt_LinuxConsole::UpdateLogError(wxString message)
{
	
	txtLog->SetInsertionPointEnd();
	txtLog->SetDefaultStyle(wxTextAttr(*wxRED));
	txtLog->AppendText( message );
	
}
