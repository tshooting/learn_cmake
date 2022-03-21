# 参考文献：https://www.cnblogs.com/zuoruining/p/11074367.html、https://kxcblog.com/post/terminal/2.tmux-tutorial/
# 1. tmux基础配置说明（ubuntu系统）
1. 使用的配置文件已经上传，cp .tmux.conf ~/.tmux.conf
2. 安装tmux之后，在命令行输入tmux进入tmux，然后使用source-file ~/.tmux.conf 可以使得tmux生效
3. tmux ls 查看当前所有的session
4. tmux a -t session的名字,就可以进入相应的session
5. tmux kill-session -t session的名字,关闭session
# 2. 关于需要修改后的配置的使用手册
1. tmux默认快捷键的前缀是 ctrl-b, 修改成了 ` (数字键1左边的那个键)
```bash
# Set Ctrl-b key bindings
unbind C-b
set -g prefix `
```
2. 垂直增加面板和水平增加版本，使用方法 是 前缀（`）和 减号一块使用就可以(垂直)；前缀和等号一块使用是水平
```bash
unbind '"'
bind - splitw -v -c '#{pane_current_path}' # 垂直方向新增面板，默认进入当前目录
unbind %
bind =  splitw -h -c '#{pane_current_path}' # 水平方向新增面板，默认进入当前目录
```
3. 切换面板 使用方法是前缀(`)和j键一块就是向上切换面板，还可以使用前缀（`）和o键，循环切换面板，也可以使用鼠标点击进行切换
```bash
# 绑定hjkl键为面板切换的上下左右键
bind -r j select-pane -U # 绑定j为↑
bind -r k select-pane -D # 绑定k为↓
bind -r h select-pane -L # 绑定h为←
bind -r l select-pane -R # 绑定l为→
```
4. 修改面板大小，使用方法是先按前缀(`)然后按ctrl,最后按j,就是当前窗口向上调整10个单元格,也可以使用鼠标进行调整 
```bash
# 面板调整大小
# 绑定Ctrl+hjkl键为面板上下左右调整边缘的快捷指令
bind -r ^j resizep -U 10 # 绑定Ctrl+j为往↑调整面板边缘10个单元格
bind -r ^k resizep -D 10 # 绑定Ctrl+k为往↓调整面板边缘10个单元格
bind -r ^h resizep -L 10 # 绑定Ctrl+h为往←调整面板边缘10个单元格
bind -r ^l resizep -R 10 # 绑定Ctrl+l为往→调整面板边缘10个单元格
```
5. 进行复制和粘贴
5.1 按住shift，不要松开，然后鼠标选中想要复制的文本，鼠标右键进行复制
5.2 粘贴也是要shift不要松开，右键粘贴
5.3 前缀(`)和[键，是开启复制模式，然后鼠标选中一系列文字，使用前缀(`)和]就可以把刚才复制的内容进行粘贴，但是这样粘贴的内容是只能在tmux里面使用其他地方都不能使用.
5.4 现在前缀(`)和v键开始复制，然后鼠标选中，然后前缀(`)和p键就可以粘贴，但是还是不能到外部