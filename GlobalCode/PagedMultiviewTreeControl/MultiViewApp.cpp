#include "MultiviewPrecompile.h"
#include "MultiViewApp.h"

BEGIN_MESSAGE_MAP(MultiViewApp, MultiviewAppTemplate)

END_MESSAGE_MAP()

MultiViewApp::MultiViewApp() : BasicMultiviewTemplate<MainFrame, OtherView, CView, CFrameWnd>()
{

}

MultiViewApp theApp;