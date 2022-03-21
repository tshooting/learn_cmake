# 1 vscode + python + debug
1. 配置.vscode文件，如果是debug当前文件("name": "Python: Current File")，如果在此文件import上级文件，就会找不到，是路径的问题
2. 还要一种方法是配置（"name": "Python: Module"），这个地方就可以从工作目录开始找，一般不会出错，在配置参数的时候，一定要一个参数，一个值，不要把所有的参数都写在一个""里面
3. 提前设置端点，快捷键F5
```json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Python: Current File",
            "type": "python",
            "request": "launch",
            "program": "${file}",
            "console": "integratedTerminal"
        },
        {
            "name": "Python: Module",
            "type": "python",
            "request": "launch",
            "module": "train_patch2pix",
            "args": [
                "--gpu",
                "0",
                "--epochs",
                "25",
                "--batch",
                "1",
                "--save_step",
                "1",
                "--plot_counts",
                "20",
                "--data_root",
                "data",
                "--change_stride",
                "--panc",
                "8",
                "--ptmax",
                "200",
                "--pretrain",
                "pretrained/ncn_ivd_5ep.pth",
                "-lr",
                "0.0005",
                "-lrd",
                "multistep",
                "0.2",
                "5",
                "--cls_dthres",
                "50",
                "5",
                "--epi_dthres",
                "50",
                "5",
                "-o",
                "output/patch2pix"
            ],
        },
        {
            "name": "Python: Module",
            "type": "python",
            "request": "launch",
            "module": "examples.visualize_matches"
        }
    ]
}
```