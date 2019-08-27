#include "WindowsMessageMap.h"
#include "Window.h"
#include <sstream>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try
	{
		Window wnd(800, 300, "Direct3D Engine");

		// message pump
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			while (!wnd.mouse.IsEmpty())
			{
				const auto e = wnd.mouse.Read();
				if (e.GetType() == Mouse::Event::Type::Move)
				{
					std::ostringstream oss;
					oss << "Mouse position : (" << e.GetPosX() << ", " << e.GetPosY() << ")";
					wnd.SetTitle(oss.str());
				}
			}
		}

		if (gResult == -1)
			return -1;

		return msg.wParam;
	}
	catch (const EngineException & e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standart Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "no details available", "Unknow Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}