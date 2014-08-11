#pragma once
#pragma comment(lib, "dwmapi.lib")

#include <dwmapi.h>

#include "hGlobais.h"
#include "hMain.h"
#include <thread>

//--------------------------------------------------
//Descrição: Esta função é o ponto de entrada da aplicação (equivalente ao main).
//Atribuições:
//	Criar e configurar a janela (form).
//	Carregar as configurações globais.
//	Iniciar a aplicação.
//Erros:
//	Finaliza a aplicação caso nao seja possivel registrar a classe de janela.
//--------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow) {
	WNDCLASSEX objWindowClass;
	MSG objMensagem;

	//Cria uma nova thread para mover o overlay sobre a janela alvo de forma assincrona.
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MoverOverlay, 0, 0, 0);

	//Configura e registra a classe da janela.
	objWindowClass.cbClsExtra = NULL;
	objWindowClass.cbSize = sizeof(WNDCLASSEX);
	objWindowClass.cbWndExtra = NULL;
	objWindowClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	objWindowClass.hCursor = LoadCursor(0, IDC_ARROW);
	objWindowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	objWindowClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
	objWindowClass.hInstance = hInstance;
	objWindowClass.lpfnWndProc = WinProc;
	objWindowClass.lpszClassName = Global::getInstance()->objMyWindow.strNome.c_str();
	objWindowClass.lpszMenuName = Global::getInstance()->objMyWindow.strNome.c_str();
	objWindowClass.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&objWindowClass)) {
		MessageBox(0, "Erro ao registrar classe!", "Erro", MB_OK | MB_ICONERROR);
		exit(1);
	}

	//Cria a janela e armazena o handle.
	Global::getInstance()->objMyWindow.hwndReferencia = CreateWindowEx(
		WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, 
		Global::getInstance()->objMyWindow.strNome.c_str(), Global::getInstance()->objMyWindow.strNome.c_str(), 
		WS_POPUP, 1, 1, Global::getInstance()->objMyWindow.intLargura, Global::getInstance()->objMyWindow.intAltura, 0, 0, 0, 0
	);

	SetLayeredWindowAttributes(Global::getInstance()->objMyWindow.hwndReferencia, 0, 1, LWA_ALPHA);
	SetLayeredWindowAttributes(Global::getInstance()->objMyWindow.hwndReferencia, 0, RGB(0, 0, 0), LWA_COLORKEY);
	ShowWindow(Global::getInstance()->objMyWindow.hwndReferencia, SW_SHOW);

	//Neste ponto, as informações necessárias já foram alimentadas. Os objetos globais já podem ser inicializados.
	Global::getInstance()->InicializarVariaveisGlobais();
	//Carrega a lista de itens
	Global::getInstance()->LoadItemList();

	//Loop de renderização.
	while (true) {
		if (PeekMessage(&objMensagem, Global::getInstance()->objMyWindow.hwndReferencia, 0, 0, PM_REMOVE)) {
			TranslateMessage(&objMensagem);
			DispatchMessage(&objMensagem);
		}

		//Função referente ao menu (o nome será trocado em breve)
		Global::getInstance()->RefreshConfig();
		Global::getInstance()->objESP.Renderizar(Global::getInstance()->objTargetWindow);
	}

	return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	const MARGINS objMargens = { 0, 0, Global::getInstance()->objMyWindow.intLargura, Global::getInstance()->objMyWindow.intAltura };

	switch (Message) {
		case WM_CREATE:
			DwmExtendFrameIntoClientArea(hWnd, &objMargens);
			break;

		case WM_DESTROY:
			PostQuitMessage(1);
			return 0;

		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
	}

	return 0;
}

//--------------------------------------------------
//Descrição: Esta função constantemente verifica a posição da janela alvo e move o overlay para sobrepor a janela alvo.
//Atribuições:
//	Verificar se a janela alvo está aberta.
//	Mover o overlay para sobrepor a janela alvo.
//Erros:
//	Finaliza a aplicação caso a janela alvo não seja encontrada.
//--------------------------------------------------
void MoverOverlay() {
	while (true) {
		Global::getInstance()->objTargetWindow.hwndReferencia = FindWindow(0, Global::getInstance()->objTargetWindow.strNome.c_str());

		if (Global::getInstance()->objTargetWindow.hwndReferencia) {
			GetWindowRect(Global::getInstance()->objTargetWindow.hwndReferencia, &Global::getInstance()->objTargetWindow.rectDimensao);

			Global::getInstance()->objMyWindow.intLargura = Global::getInstance()->objTargetWindow.rectDimensao.right - Global::getInstance()->objTargetWindow.rectDimensao.left;
			Global::getInstance()->objMyWindow.intAltura = Global::getInstance()->objTargetWindow.rectDimensao.bottom - Global::getInstance()->objTargetWindow.rectDimensao.top;

			DWORD dwStyle = GetWindowLong(Global::getInstance()->objTargetWindow.hwndReferencia, GWL_STYLE);

			if (dwStyle & WS_BORDER) {
				Global::getInstance()->objTargetWindow.rectDimensao.top += 23;
				Global::getInstance()->objMyWindow.intAltura -= 23;
			}

			MoveWindow(Global::getInstance()->objMyWindow.hwndReferencia, Global::getInstance()->objTargetWindow.rectDimensao.left, Global::getInstance()->objTargetWindow.rectDimensao.top, Global::getInstance()->objMyWindow.intLargura, Global::getInstance()->objMyWindow.intAltura, true);
		} else {
			MessageBox(0, "Não foi possível localizar o processo!", "Erro", MB_OK | MB_ICONERROR);
			exit(1);
		}
		Sleep(1000);
	}
}