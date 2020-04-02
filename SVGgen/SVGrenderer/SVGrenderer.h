// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/dcsvg.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#ifdef SVGrenderer_EXPORTS  
#define DLLIMPORT __declspec(dllexport)   
#else  
#define DLLIMPORT __declspec(dllimport)   
#endif  
extern "C" {
	void DLLIMPORT RunApp();
}

