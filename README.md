### 博客方案 ###

#### 博客关键点 ####

* 博客内容采用`markdown`编写
* 采用`blog.list`记录博客的细节内容 [_主要解决创建时间的问题_] 
* 静态网页模板以及相关的`js/css`实现处理好

#### 具体使用用例 ####
##### 添加新博客 #####
```
./scripts/blog.py add $title $filename
```
_`$title`与`$filename`是对应的标题内容与md文件_

##### 修改现有博客 #####
```
./scripts/blog.py change $filename
```
_`$filename`是对应的md文件_

##### 重新生成所有博客网页 #####
```
./scripts/blog.py change
```
