1. git status
* 通常我们使用 -s 参数来获得简短的输出结果：AM是添加到缓存(add file)之后有改动(在工作区有带动但是还没有添加进来)，A是新增
2. git diff 
* git diff file :比较文件在暂存区域(git add )和工作区的差别
* git diff --cached(或者是--stage) file 显示暂存区和上一次提交(commit)的差异
* git diff [first-branch] ... [second branch]:显示两次提交之间的差异
3. git commit 暂存区到本地仓库
* git commit file1 file2 -m "msg"
4. git reset 
```bash
git reflog #查看所有的历史版本 b0ea5cc HEAD@{2}: commit: add_11_12_head2 b0ea5cc就是版本号
git reset --hard b0ea5cc #工作区，暂存区，本地仓库等都会回到b0ea5cc版本，无论在执行命令之前做了多少改动都会被撤销，回退到b0ea5cc版本
git reset --soft b0ea5cc # 不改变本地工作区和暂存区，改变的是commit的内容
```
5. git rebase
https://www.waynerv.com/posts/git-rebase-intro/
```bash
git pull origin master
git checkout orther_branch
git rebase master
```
6. git add
```bash
git add . # 将所有的文件都加入到暂存区
git commit 指定文件 -m "msg" # 将暂存区的指定文件或者全部文件 都加入到本地仓库
git push origin master # 将本地仓库的东西都推送到远程仓库
git rm --cached 文件 # 在暂存区删除文件，删除add的文件，但是本地工作区不变
# 如果commit 失败，或者想删除commit的文件，目前想到的办法是
git reflog #查看所有的提交 假设想删除的是HEAD@{0} 那么就恢复到上一个版本 HEAD@{1} 查看 HEAD@{1}前面的commit_head1_id
git reset --soft commit_head1_id # 不改变本地工作区的代码，只是提交的修改
```