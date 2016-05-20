cmake_minimum_required (VERSION 2.8)

set(SRC_FILES
	GameCanvas.cpp
   )

set(LIBS
	TicTacToe
	WidgetLib
   )

add_executable(MNK_Gui "main.cpp" ${SRC_FILES})
target_link_libraries(MNK_Gui ${LIBS})
