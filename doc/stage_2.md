# Stage 2
## to-do lists
- [x] 词条搜索 (通过SQLite 数据库索引实现速查)
- [ ] 还希望能够对词典内容进行分析
- [ ] 研究GoldenGict是如何显示html页面的

  - 找到一个 ArticleView 类
- 研究GoldenGict是如何管理资源的
- 找一个合适的文档编辑器
  - 支持markdown
  - 支持数学公式
  - 像onenote一样简洁自然
- 重新调整词典的顺序
  - 能够把短语搭配放在最后，避免长时间翻页。比如back这个词
## goldendict
- ArticleView 类
  - ArticleView 是 QFrame的一个子类
    - 在一个界面中显示多个字典的内容
  - sptr 自定义的 smart pointer
  - Dictionary : Abstract dictinary-related stuff
  - Instacnes 
  - Config : GoldenDict's configuration
  - fts 是 full text search的意思
- MainWindow 类
  - 找到两个个关键的函数 void translateInputChanged( QString const &);
  - void translateInputFinished( bool checkModifiers = true );
  - 这个 respondToTranslationRequest
  - showTranslationFor
  - 最后找到了真正的处理搜索任务的函数 showDefinition
  - 发现GoldenDict 执行了 SQL语句查找，然后不知道怎么就变成一个链接，然后可能被AriticleMaker合成为一个网页
  - 看了GoldenDict 目前的实现方式，需要很多web编程的知识，我现在先不这样实现
  
## Reading Stack
- 人学习的知识是一个树状结构，人的注意力是一个栈结构
- 把知识数分解成学习栈来进行学习
- 是做成卡片形式，还是挂历形式？