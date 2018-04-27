######以学习和实现目的的简单图像处理库，使用directx作为显示以及调试手段

##实现算法
* 基本
    * bmp位图读取（位深度4、24、32）  
    * D3DCOLOR（显示矩阵）与Mat（运算矩阵）转换
    * 灰度化
    * 字符绘画ascii art
* 变换  
    * 傅里叶变换dft  
    * 傅里叶逆变换idft
    * 傅里叶频谱显示  
* 滤波  
    * 线性滤波  
        * 方框滤波
        * 均值滤波
        * 高斯滤波
    * 非线性滤波  
        * 中值滤波
        * 双边滤波
* 形态学
    * 膨胀
    * 腐蚀
    * 开运算
    * 闭运算
    * 形态学梯度
    * 顶帽 
    * 黑帽
* 边缘检测
    * soble,Prewitt,Scharr算子
    * Laplace算子
    * 阈值处理（基础）
    * hough变换（直线检测）


下面的字符画放在各类字符宽度一致的记事本上查看没问题的(/≧▽≦)/ 
github页面咋就乱了呢┭┮﹏┭┮











..................................................................................................Íýýýý
................................................................,:::;;;oo;........................Íýýýý
..............................................................,;ooxxxxxxx:..............,.........Íýýýý
............................................................,,;oxxxxxxxxo,,..........,,,:,,.......Íýýýý
................................................,,,:,,..,,,,,ooxxxxxxxxx:,,,.......,,:;xxo;,,,....Íýýýý
..............................................,,:;oo;,,,,,:;ooxxxxxxxxxxoo;::,,,,,,:oxx%%%xo;,,,..Íýýýý
............................................,,:ooooo;:;;ooooxxxxxxxxxxxxxxxxxo;:::oxx%%%%%%%xo:,,.Íýýýý
...........................................,;ooooooooooooooxxxxxxxxxxxxxxxxxxxoxxxx%%%%%####%%xo:,Íýýýý
..........................................,oooooooxxxoooooooooxxxxxxxxxxxxxxxxxxxx##@@#######%%xo:Íýýýý
.........................................,;oooxoxoxoooxxxxxxxxxxxxxxxxxxxoxxxxxx%###@@@@#@###%%x;,Íýýýý
........................................,:oooxxooooxxxxxxxxxxxxxxxxxxxxxxxooxxxx#@@@@@@@#@##%%x;:,Íýýýý
.....................................,,,;oooooooxooxxxxxxxxxoooxxxoxxxxxxxxxxxx%@@#@@@@@#@##%x;::,Íýýýý
...............................,,::,,,;oooooooxoooooo;;;;oxxoo;;oooooxxxxxxxxxx%###@@@#@#@@#x;::,,Íýýýý
..............................,,;oo;;ooooooooooo;:,,,,::oxxoo,,,,,:;ooxxxxxxxx%#%###@@##%@@%o;::::Íýýýý
............................,,:ooooooooooooo;:,,,,,,,,,;xooo,,...,,,,;oxxxxx%%#%%###@@@##@@%o;:,::Íýýýý
...........................,,;oooooooooooo:,,,o%##@##%xxxoo:,.......,,,ooxxx%#########@@#@##o;::::Íýýýý
..........................,;ooooxxooooo;:,,:x###@@@@@@@#%%;,..........,,;ox%##@@@#####@@@###%o;::,Íýýýý
.........................,:oooxxooxoo;,,,.o###@@@@@@@@@@@@#o............,:x%%###%%###########xo;;;Íýýýý
.........................,;ooxooooo;,,,..x#@#@@@@@@@@@@@@@@#x............,;x%x%%x%###########%xoooÍýýýý
........................,,ooooooo;:,,...o###@@@@@@@@@@@@@@@@#x...........,,x%%%x%#####@@###@##%%%%Íýýýý
.......................,,;oooooo:,,....:%##@@@@@@@@@@@@@@@@@@#o...........,;xxxx%#######@##@######Íýýýý
......................,:ooooxo;,,,....,x%####@@@@@@@@@@@@@@@@@#:...........,;xxxx%####@@@%#####%##Íýýýý
.....................,:oooooo:,,.....,;x#%##@@@@@@@@@@@@@@@@@@@%............:xx%x%%############%##Íýýýý
...................,,;ooooo;,,,....,,,x%####@@@@@@@@@@@@@@@@@@@#;...........,oxxx%%###############Íýýýý
................,,,,;ooooo:,,....,,:;o%######@@@@@@@@@@@@@@@@@@@%...........,:xx%%####@@@#########Íýýýý
..............,,;;ooooooo:,,....,,;ooo%%#%#%#@@@@@@@@@@@@@@@@@@@#,..........,,xx%#####@@@#########Íýýýý
.............,,oooxooooo,,,...,,:oooox%%##%%####@@@@@@@@@@@@@@@@#;...........,ox%#%%#%#@@@@#######Íýýýý
............,,ooooxxxoo,,....,,;ooo;,;%###%#####@@@@@@@@@@@@@@@@#o...........,;x%###%###@@@#@#####Íýýýý
...........,,ooxxxxxoo:,,,..,:;oo;:,.o%###%######@@@@@@@@@@@@@@@@x...........,;xx%%#@##%##########Íýýýý
...........,oooxxoxxoo;:,,,,:ooo;,...o%##%%#%%%##@@@@@@@@@@@@@@@@%...........,;ox%%%####@@@####%##Íýýýý
..........,ooxxxoxxxxxoo;;:;ooo:,....o%#####%%%##@@@@@@@@@@@@@@@@%...........,;ox%%####@########%%Íýýýý
..........;ooxxoxxxxoxoooooooo:,.....o%#@###%%###@@@@@@@@@@@@@@@@%,..........,;x%%%######@#@######Íýýýý
.........,:oxxxxxooxoooooooo;,,......o%#@###%%###@@@@@@@@@@@@@@@@#:..........,ox%%%%##%%###@@####%Íýýýý
.........,,oxoxxo:,:;ooooooo,,.......;%#@@#@##@@@@@@@@@@@@@@@@@@@#:..........,xx%%%%%%%###@#@#%##xÍýýýý
.........,;oxoxo:,,,,,:oooo:,........;##@@@###@@@@@@@@@@@@@@@@@@@#:.........,:xx%x%%%%%%%#@#@@#%%oÍýýýý
........,:ooooo:,...,,:ooo:,.........:#%@@@###@@@@@@@@@@@@##@#@@@#:.........,;%x%%%%%%%%#@@#@##%x:Íýýýý
.......,:ooooo;,....,,;oo;,..........:##@@@###@@@@@@@@@@@@%@@#@@@#:.........,o%%%%%%%%%%%##%@##%x,Íýýýý
......,,oooooo,,....,:oo;,...........,##@@@#@@@#o%#%@@@@#@#xoo@@@#:.........,x%%%%##%%%#%##%#@#%;:Íýýýý
....,,,;oooxo:,.....,ooo:,...........,##@%%##@#%%#@@#@@@#o,::;@@@#:........,:x%%%x%%#%%%###%#@#%:,Íýýýý
...,,;ooxoxx;,.....,;ooo,.............##@x%##@@##%xo:;%#x::::;@@@#:........,ox%%%%%##%#%#####@%;,.Íýýýý
.,,;xxxxxxxo,,.....,ooo;,.............%%@xx@#@#::,:,:::;;::::o@@@#,.......,:xx%%%%###%#%######%:,.Íýýýý
.,oxxxxxxxx;,.....,:ooo,..............%%@@o@#@#:,,,,::::;::,:x@@@#.......,,;xxx%%%%%#########%x,..Íýýýý
,:x%%%xxxxo,,.....,oooo,..............x%@@#@#@#:,,,,::::;::,:x@@@#....,,,,:xxx%#%############%o,..Íýýýý
:ox%%%xxxx;,......,ooo;,..............o#@@@@#@@::,,,:::;;:::;#@@@#.,.,,,,:;xx%####%##########%o:,,Íýýýý
oxx%%%x%xx,,.....,:ooo;,..............o#@@@@#@@;:,::::::::::o@@@@#;:,,,,,:xx%%%%%######@#####%o;:,Íýýýý
x%x%%%xxx;,......,;ooo;,..............x##@@@@@@o:::::::::::;@@@@@#oxo;:,:;x%%%#%###########@#%o;::Íýýýý
x%%%%%%%x:.......,;oooo,..............x#@@@@@@@#;::::::;;::%@@@@@#xxxooo;xx%%###########@@####%x;:Íýýýý
%x%#%%%%o,.......,;oxoo:,.............%#@@@@#@@@%o::::::::x@@@@@@#xxxxxxxx%%%######%#####@@####%x:Íýýýý
xx%%%%%x;,.......,ooxxo;,,............##@@@@@@@@oxx;:::::o@@@@@@@#%%%%%xxxx%#######%##@#@@@####%%oÍýýýý
;xx%x%%x:,.......,;oxxxx;,,..........,##@@@@@@@#:x%%xo::;%@@@@@@@#xx%%%%x%%%####%#####@#@@@##@@#%%Íýýýý
o%%%%%xo,........,:oxxxxx;,,,.....,,,:#@@@@@@#@%;:xxxx%xxx@@@@@@@@%%%%%%%%%%####%x###@@#@@@#@@@###Íýýýý
x%%xx%x;,.........,oxxxxxxo;:,,,,,:;;x#@@@@@@@@oo,%oox:;ox#@@@@@@@#%%%%%#%%#%###%%###@##@@@#######Íýýýý
x%%%%%x:,.........,;oxxxxxxoooooooooox##x;,@@@@;::%%%xo;ox%#@@@@@@#%%%%%%%%#%##%%#@##@###@#@######Íýýýý
x%%%%%x:,.........,:oxxxxxxxxxoooooooo:.,,:%@@#,,;x;:;;oxxxx@@@@@@#x%%%%##%#%#####@##@@@###@@@@###Íýýýý
%#%%%%x,,.........,:oxxxxxxxoxoooooo:,,:;::%@@#.,oo;oo;oxx%x@@@@@@@%%%##%###%#%#@#####@@@@@@@####%Íýýýý
%#%%%xx,,........,,ooxooxoooooooooo:,,:::::o@@@,,xo;;ooooo%x@@@@@%x#%#%#%##%%##@@@##@##@@##@@@@###Íýýýý
%#%%%xx,,.......,,ooooo;;;oooooo;;;..,,,,,,;@@@.,%o:oxo;o%%%@@@@@o::o#%%%%###%##@####@@####@@@@#@#Íýýýý
%###%xx,,.......,;oooo;,,,,::::::;,..,,,,,,,%@@,;@o:oox;o#%%@@@@@;;,,;x#%%%%%%#@@@#####@@@@@@@@#@#Íýýýý
%#%#%%x:,......,;oooo;,,....,.,o%;...,,,,,,,;%@;x@:;o%;:%%%%#@@@@:,:,,:x%xxx%%####%##@@#@#@@@@@###Íýýýý
%%%%%%x:,.....,;oooo;,.......:oo%,...,,,,,,,,;@ox@:;;@;o%xoo%@@@@;:,,,.,xxx%xx%@#@###@@@@@@@@@##@#Íýýýý
#%%%%%x;,...,,:ooooo,.......:o;;o,...,,:,,,..,xxo@:;%@o%o;;;x@@@@::,,:,,;xxx%%#####@#@@@@#@@@##@@#Íýýýý
#%%%%%xo,,.,,:ooooo,.......,o;;oo,...:,,::,.,,:x%@#%@#%;::::o#@@@:,,,,:::xxx%########@@@###@@##@@#Íýýýý
#%%%%%xx,,,,:ooooo,,.......:o;;ox:..:,,,;:.,,.,:#@@@@oo,.,,:o#@@#::,.:;;;x%%#########@@@###@@@#@@#Íýýýý
%%%%%%%x:,,:ooooo:,........,o;xo%:,:;::;;,,,,...#@#@@:.....,:@@@x,:..;;;;x###########@###@@#@@####Íýýýý
#%%%%%%xo::oxooo:,..........ooxo%o;;;;;o;,,...,,#@@@;...,,,,,@@@o;,.,;;;ox##%#######%@###@@#####%%Íýýýý
#%%%%%%%x;xxxoo;,...........oo%x%%;;;ooo;......,#@@%:....,,,,@@@;:,,;;;oox%#%##%%%#############%xoÍýýýý
##%%%%%%%xxxxo;,...........:#%%%%%o;ooxx:......,%@@,....,,,::@@@,,,;;;;ox%xx%#%xxxx%%%%#######%xx;Íýýýý
%%%%%%%%%xxxxo,,..........:x#x%##%#xoo%x,......,##%,....,::;o@#@:,:;::oox%%oox;,,:;oxx%%%####%xx;,Íýýýý
%%%%%%%%%xxxx:,...........x%x#%%#@@@#@%:,......;@@o...,,,,::;#@#;:;::;ox%xooxx:,,,,,,,;ox%%%%%xo,,Íýýýý
#%%%%%%%x%%xo;:,.........;x;x%x@@@@@@#o,,......x#@:...::::::o#@%o;;:;o%%xxoxxxo.......,,:;oxxxo,..Íýýýý
%%%%%%%%x%%xx%o:,.......,xo;;x#@@@@@@#,,......,###....::;;;o%@@xo;::xxxoxxxxxxo.........,,,,::,...Íýýýý
%%%%#%#%%%%%%%xo:,,,.,..oxoooox%#@@#@x,,,.....;##x........,,%@@xx;;xooox%%%%xo..............,,....Íýýýý
%%###%###%%xxxxxxx;:,,,:ooooooox###;#o,,,,....%#@:.........:@#@xxoxooxx%%%%%%,....................Íýýýý
%%%###%@#%%%%%%%#xxx;;;ooooooxx##%xx%;,,,,,..,###.........,%@@@x%xxxxxxxx%##%,,...................Íýýýý
%%%##%%######%%##%%%xoooooooox%#%x%x#;:,,,,,,;#@x,...,...,oo#@@x#%%xxxxx%###%.,,,,,,..............Íýýýý
%%######@@########%%xxoooooox%##%xxx#o:::,,,,%@@o,,..,......#@@%##%xxxx%###%o,,:o;:,,,............Íýýýý
%%%##########@@@@###xxoooox%###%%%%%#%:;:::::@@@o:,,,:...,,,#@@%@#%%%%###@#;,,:ooooo;:,,..........Íýýýý
%%%##%#######@@@@#@#xxoxxx%%%x%#%####%;;;;;;;@@@o::,,::,::::@@@%#@#@#@@@@@;:::oxoxxxoo;;,.........Íýýýý
%%%#%%%######@@@####%xox%%#%#%#@#@@##xx;;;;;o@@@o;;;;;;;;;oo@@@##@@@#@#@@@xoooxxxoxxxoo;,.........Íýýýý
%%###%%#%%#@##@@@###%xooox%#%%@@@@@##x#;oo;;%@@@ooo;;;oooooo@@@#####%#%@#%xo%#%#xxxxxxo;,.........Íýýýý
%%%%##%#%%#######@@@%xoxxxxxx#@@@@@#%%@;;oo;%@@@ooooooooooxx@@@#@%%%%%%%%%%##%%%xxxx%xo:,.........Íýýýý
%%xxx%%%####%#@@@#@@%xxoxx%#%@@@@###%#@;:;o;#@@@xooooooooxx%@@@#@%%%xxx%%%%####%%%%%%%x:,.........Íýýýý
%%xxxxx%%%%%%##@@@@#%xooooxx%@@@@@##x#@;,:;;#@@@xooooooooxxx@@@##%%%xx%%##%###%%%%%%%xx:,.........Íýýýý
xxoooox%%%%%%##%####%xooooox%#@@@#@@x##;:,::@@@#xo;;;oooxxxx@@@##%%%xxx%##%##%###%%%%%%o:,,,......Íýýýý
xxoo::oxx%x%%%#%#@@@%xoo;oox%#@@##@@x##;:,,:@@@#o;:;;;ooxxxx#@@#@%%%%%%%##%####%#%%%%%%xx;,,,,,,:.Íýýýý
xo;,,,,;xxxx%%x%#@@@%xoo;oo%x%@@#@@@%#%;:,,;@@@#o;;;;;;oooox#@@#@%%%%%%%##x####%#%%%%%%%%%o:,,;;;,Íýýýý
x;,,..,:;oxxx%%####@#xoooox%xx@@#@@#%@x;,,.o@@@#;;;::;;;;ox%@@@#@%%%%%%%#%x####%%#%%%%##%%%o;oooo;Íýýýý
:,....,,,:;xx%%##%#@#xo;oox%%x@@@##%#@;;,..%@@@%;:::::::;x%%#@##@%%%%xx%#%x########%###%#%%%xoooooÍýýýý
,........,:x%%%%##@@#oo;oox%%x%@###%##::,..@@@@%:::::::;x%%%#@##@%%%xx%%#%x#%%%##%#%##%#####xoooooÍýýýý
.........,:x%%%%%#@@@oo;oox%%%x@%%%x#%::...@@@@%:,,,::;oxxx%#@#@@%%%%x%%#%xxx%x%#%%x%%%#%#%%#%xoooÍýýýý
.........,;x##%%%#@#@xx;oox%%%x%xxx%@o::..:@@@@%:,,::::;;x%%#@%#@%%%%%%##%xx%xxoo%%x%%#%%##%%%%xooÍýýýý
.........,;x########@xxoooox%%xo:;;%@;,:..o@@@@x:,,,,,,;x%%%##%##%%%%%%##%x%xx;::;ox%###%%####%xo;Íýýýý
.........,o%#####@@@@xxoooxx%%%x:,;##,,:..%@@@@x:,,,,,:xxx%%#@##@%%%%%%##%%xoo,,,,,;%%%%%%####xo;,Íýýýý
........,,x%%#####@@@xxoooxx%%#%;.o#x,.,..#@@@@x,,,,,oxxx%%%%@##@%%%%%%##%xxo:,...,,:x%%%%###%o;,,Íýýýý
........,:x%%%#####@@xx;oxox%##%;,x#;,..,,@@@@@x,,,;oooox%%%#@#@@%#%%%%##%%x;,.....,,:x%%x###%o;,,Íýýýý
........,;x%%%#######%x;oox%###%x:##:,..,;@@@@@o,,;;;::;o%%%###@@%%%%%###%%o,,......,,oxxx###%o;,,Íýýýý
........,ox%%%##%####%x;oox%###%xx#%:,..,x@@@@@o,,,::,:;x%%%%#@@@%%%%%###%%;,.........:oxx#%%%%o:,Íýýýý
.......,:ox%%%%%##%##%x;oox%%%####@;,....#@@@@@x,,:,..:oxx%%%#@@#%%%%%####%:,.........,;xx##%%#o::Íýýýý
........:ox%%%%%#####%xooox%#@%xx%x:,....@@@@@@x:,,.,,;;o%%%%#@@##%%%%####%:,.........,:ox%##%#%xxÍýýýý
........:ox%x%%###%%%%xooox#@ooxx%;,,,.,;@@@@@@o:,,,,,:;x%%%%#@@#%%%%%####x;,..........,oxx%%%%%x%Íýýýý
........,oxx%%%%#%%x%xxoox%#;o;o:o:,,:::%@@@@@@o,,,,,:;;o%%%%#@@%%%%%%####xo;,,........,oxx%%%#%%%Íýýýý
.........::;xx%%%%xxxxxxxx#oo:;::o;:.,::o@@@@@@::::,::;oox%%%#@@%%%%%###%%xo;;,........,;ox%%%#%%%Íýýýý
...........,:;;oxxxoxxxxx%%;;o:o:x:;:.,::@@@@@x;;:::;oooxx%%%#@#%%%%%##%%%xoo;:........,;ox%%##%%%Íýýýý
.............,,,::::;ooxx%x;;o:o;@:;;:..,x@@@%o;:;;;;;;;;ox%%#@#%%%%%##%%%xo;;;,.......,;o%%##%x%%Íýýýý
...............,,,,,,,,x%%ooo:;oo@@o:::,.,@@#o;;;;::::::;x%%##@#%%%%%#%%%%xo;;;:.......,;o%%%x%xx;Íýýýý
.....................,.o%%oox:;o%x@@%:,:,,%@xoo;;:,:::;oxxox%#@#%%%%%%%%%%xo;o;:.......,;oxxxox;:,Íýýýý
.......................:x%%oxx;:x%%#@@x:,:;ooo;;:::::;oxxxxx%#@%%xx%%#%%%%xo;;;:......,,oox%%o:,,.Íýýýý
........................o%#o#%oxxx#x;#@@#x;;::,::::;ooxxxxx%##@%xxxx%%%%%%%o;;;:......,:oox%%o:,..Íýýýý
........................,o%x%@#%xx%x::ox%%#@@#xxoooxxx%##@@@@#@%%x%x%%%%%#%x;;;:,.....,:ooox%:,...Íýýýý
.........................;oxx%%%@#@x::;xx%xxx%%#@@@@@@@@#%ooo##%%%%%%%%%%%%xo;;:,...,,,oooo%o,,...Íýýýý
........................,;ooox%#@@@#;:;xxxxxxxx%;;;;o@;:;;;;x@#%%%%%#%%%%%%oo;;,,,.,,,;xx;ox;,,...Íýýýý
.................,......,;x##@##@@@@@%x%xxxxx%%#o;;;o@;;;ooox@#%%%%%#%%%%%%oxo:;::,::;xxooxoo;:...Íýýýý
..............,:;:,,.,,,,o#%####@@@@@@@#xxx%%###o;;;o@;;oo%#@@%%%%%%#%%%%%xox%xxooooox%oo%oo;;:...Íýýýý
.............,;ooo:;:::;ox%%%%##@##@@@@@@@@@@####%%%#@#@@@@@@@%%%%%##%%%%%xxx#%%ooox%%xo%ooo;:....Íýýýý
.............:ooxxooo;;;x%#%#####@@@@@@@@@#@@@@@@@@@@@@@@@@@@@#%%%%##%%%%%xox%%%oox#%xo%xoo;;,....Íýýýý
............,:oox%xx%%%#######%#@@@@@@@@@@@@@@@@@@@##@@@@@@@@@%######%%%%%xoo%%%o%%%%x%xooo;,.....Íýýýý
.........,,,:;oxx%x%%%#@##@#####@@@@@@@@@@@#@@@@@@@@##@@@@@@@@%#####%%%%%xxxo%%%%x%#%#xoo;;:,.....Íýýýý
........,:;;;oxx%xxx%######%%%%#@@@@@@@@@@@#@@@@@@@@@@@@@@@@@@%#########%%xxox#%xo#ox%oo;:,,......Íýýýý
........,;;oxxxooxxxx%%#%%%###%#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%##########%%xox%%;%oo%ooo,,........Íýýýý
........:;;oxoxoxxooox%%%%%#@#%#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@############%xxx###xox#x:,..........Íýýýý
.........:;;o;oooo;;;;;ox%%#@@%##@@@@@@@@@@@@@@@@@@@@@@##@@@@@@###########%xox###x%x;:,...........Íýýýý
.........,;;;;oo;:;;:,,,:ox%#@#%%#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@############%x%####%o::,...........Íýýýý
.........,;;;;;;,,,;;,,,,:ox%##%%##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@########@@@#%@%##xoo;:............Íýýýý
........,,;o;;;,..,:;:,,,,;ox%#%%#@@%@@@@@@@@@@@@@@@@@@@@@@@#@#@@@@@@@@@@@##@###%ox::,............Íýýýý
.......,:;;;;;,....,;;,,,,:ooxx%%@@@%##@@@@@@@@@@@@@@@@@@@@@#@@@ooxx%%xxxxo%##%%%%x;,.......,.....Íýýýý
.......,;;;;;:.....,:;:,,,,;oxx%%#@@%##@@@@@@@@@@@@@@@@@@@@@#@@@o;;oooooo;:##@#%xo:;,.......:.....Íýýýý
.......,:;;;;:.....,;;;;::::o;o%%#@@%##@@@@@@@@@@@@@@###@@@@#@@@x;:,::;;ox#@@##%x;;:.,.....::,....Íýýýý
........,;;;;:....,;;;;;;oo;;oox%#@@%##@@@@@@@@@@@@@##x%##@@@@@@@%xoxo%%@##@@@#xx;;,,,.....:o.....Íýýýý
.........,:;;:....:;;;:,:;o;xoxx###@###@@@@@@@@@@@@##%x%##@@@#@@@@%x%%%@@##@@@%%oo;;:::,..,o;.....Íýýýý
..........,;;:....:;::,..,:;oxxx###@####@@@@@@@@@@@@##x%%##@@#@@@@%%##@@@##@@#%xxo;::::,.,;x:.....Íýýýý
..........,;;:....;:,,....,,;oxx#%#@@###@@@@@@@@#@@@##%%##@@@#@@@@@@@@@@#x%@@%%xxo;::,,,,oo;,.....Íýýýý
..........,:;;,...::,......,:;x###@@@###@@@@@@@##@@@@#####@@@@@@@@@@@#%xxo#@@#%xox;::,..:oo:......Íýýýý
..........,;;;:,.,::,.......,:;%%%@@@##@@@@@@@@##@@@@@####@@@@@#%%xooxxxxx####%xox;;::::;x:,......Íýýýý
..........,:;;;::::;,.......,::x%%@@@##@@@@@@@@#@@@@@@####@@@@::::;oxxxxoo####%%xxo:,,,.;;:,,.....Íýýýý
...........:;;;;;;;::,...,,..,,x%%#@@@@@@@@@@@@##@#@@@#####@@@ooooxxo;ooox##@##%xx;:,,,.:.........Íýýýý
...........,:;;;:,,,:,...,,,.,,o%%%@@@#@@@@@@@@#%@#@@@@####@@@o;;;;;;;ox%%###@#xxo;:::,,:.........Íýýýý
............,,:;:,..,:,...,..,,o%x%#@@@@@@@@@@@#%#@@@@@####@@@x;;ox%%%%##%#%###%%o;;;:;;,.........Íýýýý
..............,:;:...,;:,,.,,,:oxxx#@@@@@@@@@@@#%x##@@@@###@@@@@@@@@%%%%#%##%%%%%;;;;;:::::,,.....Íýýýý
...............,:::..,::::,,:::oxxx#@@@@@@@@@@@#%xx#@@@@###@@@@@@@@@%%%%%%%%%#%%xo;:;;;;;:,:,.....Íýýýý
,..............,:;::,.,,:;;::;;oxxx#@@@@@@@@@@@#%xx#@@@@@##@@@@@@@@@%%%%%%%%x%%xxo;:;;o;:::,,.....Íýýýý
,.........,,,..,:;;;:,,,,,:;o;;oxx%%@@@@@@@@@@@#x%%%@@@@@@@@@@@@@@@@%%%%x%%%%%%oxo;;;:o;:;::,.....Íýýýý
.......,.,,,,...,;;;;;;,,,,:o;:oxx%%@@@@@@@@@@@#xxx%#@@@@@@@@@@@@@@@%%xx%%%x%x%xo;;:::,::::,,.....Íýýýý
....,,,,,..,..,,,,:::;o;::::;o;oo%%%#@@@@@@@@@@#xxxx#@@@@@@@@@@@@@@@%%%xxx%x%%%xoo:::,,:::,,......Íýýýý
....,,...,,,,,,.....,;;;;;:::;;;o%%%#@@@@@@@@@@#xxx%#@@@@@@@@@@@@@@#%%xoxxx%%xxo;:::,,............Íýýýý
