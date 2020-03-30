#include "SVGrenderer.h"

class MyApp : public wxApp
{
public:
	bool OnInit()
	{
		wxDialog* dlg = new wxDialog(NULL, -1,
			"Hello World From Library", wxDefaultPosition, wxDefaultSize,
			wxDEFAULT_DIALOG_STYLE, wxDialogNameStr);
		dlg->Show();
		return true;
	}
};

static wxAppConsole *wxCreateApp()
{
	wxAppConsole::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "my app");
	return new MyApp;
}

// The only public function, declared also in library's header.
void RunApp()
{
	wxApp::SetInitializerFunction(wxCreateApp);
	wxEntry(0, NULL);
}