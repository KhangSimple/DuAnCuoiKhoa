## Báo cáo bài tập lớn môn Lập trình nâng cao - INT2215_1
1. Hướng dẫn cài đặt
    - Cần thêm một số bước cài đặt thư viện để chạy chương trình bao gồm :MinGW-W64, SDL2 ,SDL2_image ,SDL2_mixer , SDL2_ttf
        - Link tải chương trình dịch : https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-win32/seh/x86_64-7.3.0-release-win32-seh-rt_v5-rev0.7z/download
        - Link tải thư viện:
            - SDL2 : https://www.libsdl.org/release/SDL2-devel-2.0.20-mingw.tar.gz 
            - SDL2_image : https://www.libsdl.org/projects/SDL_image/ (Chọn phiên bản phù hợp với máy)
            - SDL2_mixer : https://www.libsdl.org/projects/SDL_mixer/ (Chọn phiên bản phù hợp với máy)
            - SDL2_ttf   : https://www.libsdl.org/projects/SDL_ttf/release/ (Chọn phiên bản phù hợp với máy và nên chọn bản mới nhất)
        - Bước Setting:
            - Đầu tiên mở "Environment Valiables" bằng cách tìm kiếm "Path"
            - Sau đó chọn "Path" rồi add các đường dẫn đến file "bin" trong các file vừa tải . Vd: C:\software\sdl_image\x86_64-w64-mingw32\bin
            - Với CodeBlocks:
                - Vào Setting/Compile/Linker settings rồi dán "-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf" vào phần Other linker options
                - Sau đó vào "Search directories" :
                    + Chọn "Compiler" :Add các đường dẫn đến "SDL2" . Vd: C:\software\SDL2-2.2.20\x86_64-w64-mingw32\include\SDL2
                                                                          C:\software\sdl_image\x86_64-w64-mingw32\include\SDL2
                    + Chọn "Linker" : Add các đường dẫn đến "lib" (Tương tự như cách add như trên)
                    *Xong thì bấm OK là hoàn thành xong bước set up đầu tiên
                    
                - Bấm chuột phải vào project rồi chọn "Build options" rồi làm các bước y như trên
            - Với VsCode: 
                + Làm theo hướng dẫn trong : https://pie-cheque-188.notion.site/C-i-t-h-a-C-Windows-ef0a99a8dcae4dae86a39dc1cbc35980
                + Trong  "Makefile": 
                    all:
	                    g++ -Isrc/include -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

2. Mô tả về game "Snake"
    - Như game "Snake" các bạn đã biết thì ở đây nhiệm vụ của người chơi là điều khiển cho rắn đi ăn táo(cherry), ăn càng nhiều quả thì điểm càng cao .
    - Game sẽ dừng lại nếu rắn đâm vào tường hoặc cắn vào thân .
    - Ý tưởng chính :Tạo sân chơi cho rắn di chuyến ăn táo bằng các nút KEY_UP , KEY_DOWN , KEY_RIGHT , KEY_LEFT sau đó tạo ra cấu trúc như các 
          game thông thường với "menu" , "score" ,"gameover" , "highscore" .

3. Các chức năng đã cài đặt 
    - Link Video : https://www.youtube.com/watch?v=uJQIP4WF0xg (có âm thanh trò chơi nhưng do lap bị hỏng mic nên không thu được) 
    - Ở đây các thao tác với game là "bàn phím".  
    - Cửa sổ "menu" với 2 mục là : "Play" và "HighScore"
        + Khi chọn "Play" thì sẽ hiện lên cửa sổ "Snake Game" và chơi trò chơi.
        + Khi chọn "HighScore" thì sẽ xem được điểm số của các người chơi từ cao đến thấp .
                (3 người chơi điểm cao nhất thì điểm sẽ có màu vàng, còn những điểm còn lại màu trắng , giới hạn là hiện 9 điểm cao nhất) .
    - Cửa sổ trò chơi : Ở đây chúng ta sẽ điều khiển rắn đi ăn các quả táo và sẽ đóng khi trò chơi kết thúc(đâm tường,cắn thân) .
    - Cửa sổ hiện điểm của người chơi  : "YOUR SCORE:..." (Cửa sổ sẽ đóng sau 1s)
    - Cửa sổ "Game Over" : Ở đây sẽ hỏi xem người chơi có muốn chơi lại không 
                                    + Nếu chọn "YES" thì sẽ chơi lại .
                                    + Nếu chọn "NO" thì sẽ quay trở về màn hình "menu" .
    - Có âm thanh khi bắt đầu chơi : Tiếng nhạc nền trò chơi, tiếng rắn ăn táo, tiếng gameover.
4. Các kỹ thuật lập trình được sử dụng trong chương trình
    - Các kĩ thuật lập trình
    	- Sử dụng mảng ,xâu ,stringstream.
    	- Sử dụng biến const, con trỏ ,tham chiếu .
    	- Sử dụng class ,struct .
    	- Tạo project với các file.ccp và file.h .
    - Với thư viện SDL2, SD2_image, SDL2_ttf, SDL2_mixer .
    	- Dùng SDL2 để tạo các cửa sổ game
    	- Sử dụng thư viện SDL2_image để load ảnh định dạng PNG/JPG .
	- Xử lí sự kiện chuột, bàn phím .
	- Sử dụng SDL2_mixer để load âm thanh trò chơi
	- Sử dụng SDL2_ttf để viết lên màn hình. (Dùng để tạo "SCORE" và "HIGHSCORE" )
5. Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thiện chương trình  
    - Kết luận và điều tâm đắc:  
    Qua quá trình làm game , em nhận thấy kĩ thuật lập trình của mình được nâng lên đặc biệt trong việc sử dụng các đối tượng, liên kết các    đối tượng để tạo ra một     chương trình hoàn chỉnh hợp logic.Và ngoài ra em còn hiểu được cách lập trình theo nhóm, tạo khung chương trình với các hàm trống và giao từng việc cho từng người,     chương trình phát triển từ từ và rất chắc chắn .Trong các thư viện thì có rất nhiều hàm có sẵn giúp công việc của chúng ta dễ dàng hơn, và mặc dù vậy thì tư duy  	 của người lập trình rất quan trọng, khéo léo trong việc sự dụng các hàm . Ngoài ra, em còn học được một số kĩ thuật code rất quan trọng như Refactor làm cho code       sạch, đẹp,dễ đọc ,hay là quy tắc tạo hàm là mỗi hàm thì chỉ làm một công việc duy nhất ,hay quá trình làm 1 project lớn là CDIO . Và em mong trong quá trình học       sau này , các thầy,cô sẽ chỉ dẫn và chia sẻ các kinh nghiệm quý báu để em có thêm những kỹ năng mới trong lập trình .
    - Hướng phát triển game
    	+ Tạo ra nhiều map hơn
    	+ Cho người chơi chọn tốc độ di chuyển của rắn
    	+ Tạo thêm nhiều item ngoài táo (quả làm cho rắn bất tử ,quả to nhiều điểm ,quả làm giúp rắn bỏ bớt một số đốt,...)
    	+ Cho người chơi nhập tên 
