#include <windows.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	//find and save all eontimer handles
	HWND eon_timer_hwnds[2];
	HWND* eon_timer_hwnds_ptr = eon_timer_hwnds;
	
	HWND first_window = FindWindowExA(NULL, NULL, NULL, NULL);
	HWND window = first_window;
	
	do{
		char window_title[MAX_PATH];
		GetWindowText(window, window_title, MAX_PATH);
		
		if(strcmp(window_title, "EonTimer v1.6") == 0){
			*eon_timer_hwnds_ptr = window;
			
			eon_timer_hwnds_ptr++;
		}
		
		window = FindWindowExA(NULL, window, NULL, NULL);
	}while(window != first_window);
	
	//sort eon_timer_hwnds
	if(eon_timer_hwnds[0] > eon_timer_hwnds[1]){
		HWND tmp = eon_timer_hwnds[0];
		eon_timer_hwnds[0] = eon_timer_hwnds[1];
		eon_timer_hwnds[1] = tmp;
	}
	
	//define inputs
	INPUT ip_d;
	ip_d.type = INPUT_KEYBOARD;
	ip_d.ki.wVk = VK_RETURN;
	ip_d.ki.wScan = 0;
	ip_d.ki.dwFlags = 0;
	ip_d.ki.time = 1;
	ip_d.ki.dwExtraInfo = 0;
	
	INPUT ip_u = ip_d;
	ip_d.ki.dwFlags = KEYEVENTF_KEYUP;
	
	printf("[Waiting for RETURN]\n");
	#ifdef DELAY
		// wait for global key event VK_RETURN
		Sleep(100);
		while(!(( 1 << 15 ) & GetAsyncKeyState(VK_RETURN))){
			usleep(100);
		}
		
		// sleep 60 frames
		usleep(1000000);
	#else
		// wait for local key event VK_RETURN
		getchar();
	#endif
	
	//Perform inputs
	HWND current_window = GetForegroundWindow();
	
	for(int i=0; i<2; i++){
		SetForegroundWindow(eon_timer_hwnds[i]);
			
		SendInput(1, &ip_d, sizeof(INPUT));
		SendInput(1, &ip_u, sizeof(INPUT));
	}
	
	SetForegroundWindow(current_window);
	
	return 0;
}