#  git 
# 1 git rebase
https://www.waynerv.com/posts/git-rebase-intro/
# 2 git fetch

# 3 git add && commit && rm 
```bash
git add . # 将所有的文件都加入到暂存区
git commit 指定文件 -m "msg" # 将暂存区的指定文件或者全部文件 都加入到本地仓库
git push origin master # 将本地仓库的东西都推送到远程仓库
git rm --cached 文件 # 在暂存区删除文件，删除add的文件，但是本地工作区不变
# 如果commit 失败，或者想删除commit的文件，目前想到的办法是
git reflog #查看所有的提交 假设想删除的是HEAD@{0} 那么就恢复到上一个版本 HEAD@{1} 查看 HEAD@{1}前面的commit_head1_id
git reset --soft commit_head1_id # 不改变本地工作区的代码，只是提交的修改
```