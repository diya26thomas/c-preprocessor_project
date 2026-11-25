all:
	gcc -Wall main.c comment_removal.c file_inclusion.c macro_handler.c -o preprocessor.exe

clean:
	del /Q *.o preprocessor.exe 2>nul || true