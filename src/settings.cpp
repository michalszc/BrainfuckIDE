#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QtAwesome* awesome_, const QColor colors[], const QFont font, const QFont commentFont, QString theme, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    awesome = awesome_;
    font_ = font;
    commentFont_ = commentFont;
    codeEditor = new CodeEditor;
    codeEditor->setFont(font_);
    codeEditor->setBackgroundColor(colors[1]);
    codeEditor->setLineNumberAreaColor(colors[2]);
    codeEditor->setLineNumberTextColor(colors[3]);
    codeEditor->setLineColor(colors[4]);
    codeEditor->cursorPositionChanged();
    codeEditor->highlighter->setMovingPointerColor(colors[7]);
    codeEditor->highlighter->setReadColor(colors[8]);
    codeEditor->highlighter->setInputColor(colors[9]);
    codeEditor->highlighter->setChangeValueColor(colors[10]);
    codeEditor->highlighter->setLoopColor(colors[11]);
    codeEditor->highlighter->setCommentColor(colors[12]);
    codeEditor->highlighter->rehighlight();
    themes = new QListWidget(this);
    currentTheme = theme;
    list = new QListWidget(this);
    const QString text[] = {
        "IDE background color: ",
        "Editor background color: ",
        "Editor sidebar color: ",
        "Editor line numbers color: ",
        "Editor current line color: ",
        "Input & Output background color: ",
        "Input & Output text color: ",
        "<> color: ",
        ",  color: ",
        ". color: ",
        "+ - color: ",
        "[] color: ",
        "comment color: "
    };
    for(size_t i=0; i < 13; ++i){
        listItems.emplace_back(text[i]+QString(colors[i].name()), colors[i]);
    }
    setup();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::changeItemColor(QColor color, int index){
    QVariantMap options;
    options.insert( "color" , color );
    list->item(index)->setIcon(awesome->icon(fa::square, options).pixmap(256,256));
    list->item(index)->setText(listItems[index-2].first.split(':')[0]+": "+color.name());
    listItems[index-2].second = color;
}

void Settings::changeTheme(){
    if (themes->currentItem() == nullptr) return;
    currentTheme =  themes->currentItem()->text();
    QFont editorFont;
    QFont commentFont;
    QColor backgroundColor;
    QColor editorBackgroundColor;
    QColor editorSidebarColor;
    QColor editorLineNumbersColor;
    QColor editorCurrentLineColor;
    QColor input_outputBackgroundColor;
    QColor input_outputTextColor;
    QColor movingPointerColor;
    QColor readColor;
    QColor inputColor;
    QColor changeValueColor;
    QColor loopColor;
    QColor commentColor;

    // load theme
    if ( currentTheme == "light" || currentTheme == "dark" ){
        QSettings setting = QsettingsJSONwrapper::open();
        setting.beginGroup(currentTheme);

        // Editor font
        editorFont = setting.value("editorFont").value<QFont>();
        codeEditor->setFont(editorFont);

        // Editor Comment font
        commentFont = setting.value("commentFont").value<QFont>();
        codeEditor->highlighter->setCommentFont(commentFont);

        // IDE background color
        backgroundColor = setting.value("backgroundColor").value<QColor>();
        setPalette(backgroundColor);

        // Editor background color
        editorBackgroundColor = setting.value("editorBackgroundColor").value<QColor>();
        codeEditor->setBackgroundColor(editorBackgroundColor);

        // Editor sidebar color
        editorSidebarColor = setting.value("editorSidebarColor").value<QColor>();
        codeEditor->setLineNumberAreaColor(editorSidebarColor);

        // Editor line numbers color
        editorLineNumbersColor = setting.value("editorLineNumbersColor").value<QColor>();
        codeEditor->setLineNumberTextColor(editorLineNumbersColor);

        // Editor current line color
        editorCurrentLineColor = setting.value("editorCurrentLineColor").value<QColor>();
        codeEditor->setLineColor(editorCurrentLineColor);
        codeEditor->cursorPositionChanged();

        // Input & Output background color
        input_outputBackgroundColor = setting.value("input_outputBackgroundColor").value<QColor>();

        // Input & Output text color
        input_outputTextColor = setting.value("input_outputTextColor").value<QColor>();

        // <>
        movingPointerColor = setting.value("movingPointerColor").value<QColor>();
        codeEditor->highlighter->setMovingPointerColor(movingPointerColor);

        // ,
        readColor = setting.value("readColor").value<QColor>();
        codeEditor->highlighter->setReadColor(readColor);

        // .
        inputColor = setting.value("inputColor").value<QColor>();
        codeEditor->highlighter->setInputColor(inputColor);

        // + -
        changeValueColor = setting.value("changeValueColor").value<QColor>();
        codeEditor->highlighter->setChangeValueColor(changeValueColor);

        // []
        loopColor = setting.value("loopColor").value<QColor>();
        codeEditor->highlighter->setLoopColor(loopColor);

        // comment
        commentColor = setting.value("commentColor").value<QColor>();
        codeEditor->highlighter->setCommentColor(commentColor);

        codeEditor->highlighter->rehighlight();

        setting.endGroup();
    }else{
        QSettings setting(QCoreApplication::organizationName(), QCoreApplication::applicationName());
        if(!setting.contains("editorFont")){
            themes->setCurrentItem(themes->item(1));
            changeTheme();
            return;
        }
        // Editor font
        editorFont = setting.value("editorFont").value<QFont>();
        codeEditor->setFont(editorFont);

        // Editor Comment font
        commentFont = setting.value("commentFont").value<QFont>();
        codeEditor->highlighter->setCommentFont(commentFont);

        // IDE background color
        backgroundColor = setting.value("backgroundColor").value<QColor>();
        setPalette(backgroundColor);

        // Editor background color
        editorBackgroundColor = setting.value("editorBackgroundColor").value<QColor>();
        codeEditor->setBackgroundColor(editorBackgroundColor);

        // Editor sidebar color
        editorSidebarColor = setting.value("editorSidebarColor").value<QColor>();
        codeEditor->setLineNumberAreaColor(editorSidebarColor);

        // Editor line numbers color
        editorLineNumbersColor = setting.value("editorLineNumbersColor").value<QColor>();
        codeEditor->setLineNumberTextColor(editorLineNumbersColor);

        // Editor current line color
        editorCurrentLineColor = setting.value("editorCurrentLineColor").value<QColor>();
        codeEditor->setLineColor(editorCurrentLineColor);
        codeEditor->cursorPositionChanged();

        // Input & Output background color
        input_outputBackgroundColor = setting.value("input_outputBackgroundColor").value<QColor>();

        // Input & Output text color
        input_outputTextColor = setting.value("input_outputTextColor").value<QColor>();

        // <>
        movingPointerColor = setting.value("movingPointerColor").value<QColor>();
        codeEditor->highlighter->setMovingPointerColor(movingPointerColor);

        // ,
        readColor = setting.value("readColor").value<QColor>();
        codeEditor->highlighter->setReadColor(readColor);

        // .
        inputColor = setting.value("inputColor").value<QColor>();
        codeEditor->highlighter->setInputColor(inputColor);

        // + -
        changeValueColor = setting.value("changeValueColor").value<QColor>();
        codeEditor->highlighter->setChangeValueColor(changeValueColor);

        // []
        loopColor = setting.value("loopColor").value<QColor>();
        codeEditor->highlighter->setLoopColor(loopColor);

        // comment
        commentColor = setting.value("commentColor").value<QColor>();
        codeEditor->highlighter->setCommentColor(commentColor);

        codeEditor->highlighter->rehighlight();
    }
    list->item(0)->setText("Font:  "+editorFont.family());
    list->item(1)->setText("Comment Font:  "+commentFont.family());
    changeItemColor(backgroundColor,2);
    changeItemColor(editorBackgroundColor,3);
    changeItemColor(editorSidebarColor,4);
    changeItemColor(editorLineNumbersColor,5);
    changeItemColor(editorCurrentLineColor,6);
    changeItemColor(input_outputBackgroundColor,7);
    changeItemColor(input_outputTextColor,8);
    changeItemColor(movingPointerColor,9);
    changeItemColor(readColor,10);
    changeItemColor(inputColor,11);
    changeItemColor(changeValueColor,12);
    changeItemColor(loopColor,13);
    changeItemColor(commentColor,14);
}

void Settings::change(){
  if (list->currentItem() == nullptr) return;
  if (currentTheme == "dark" ||  currentTheme == "light"){
        currentTheme = "custom";
        themes->setCurrentItem(themes->item(2));
  }
  QString currentItem =  list->currentItem()->text();
  QString itemType = currentItem.mid(0,currentItem.lastIndexOf(":"));
  QString itemValue = currentItem.mid(currentItem.lastIndexOf(":")+1).replace(" ", "");
  bool ok;
  if ( itemType == "Font" ){
      QFont newFont = QFontDialog::getFont( &ok, font_, this);
      if (ok){
          font_ = newFont;
          list->currentItem()->setText(itemType+":  "+font_.family());
          codeEditor->setFont(font_);
      }
  }else if( itemType == "Comment Font" ){
      QFont newFont = QFontDialog::getFont( &ok, commentFont_, this);
      if (ok){
          commentFont_ = newFont;
          list->currentItem()->setText(itemType+":  "+commentFont_.family());
          codeEditor->highlighter->setCommentFont(commentFont_);
          codeEditor->highlighter->rehighlight();
      }
  }else{
      QColor newColor = QColorDialog::getColor(QColor(itemValue), this, "Choose color");
      if ( newColor.isValid() ){
          QVariantMap options;
          options.insert( "color" , newColor );
          list->currentItem()->setIcon(awesome->icon(fa::square, options).pixmap(256,256));
          list->currentItem()->setText(itemType+":  "+newColor.name());
          switch(list->currentRow()){
          case 2:
              setPalette(newColor);
              break;
          case 3:
              codeEditor->setBackgroundColor(newColor);
              break;
          case 4:
              codeEditor->setLineNumberAreaColor(newColor);
              break;
          case 5:
              codeEditor->setLineNumberTextColor(newColor);
              break;
          case 6:
              codeEditor->setLineColor(newColor);
              codeEditor->setReadOnly(false);
              codeEditor->cursorPositionChanged();
              codeEditor->setReadOnly(true);
              break;
          case 9:
              codeEditor->highlighter->setMovingPointerColor(newColor);
              codeEditor->highlighter->rehighlight();
              break;
          case 10:
              codeEditor->highlighter->setReadColor(newColor);
              codeEditor->highlighter->rehighlight();
              break;
          case 11:
              codeEditor->highlighter->setInputColor(newColor);
              codeEditor->highlighter->rehighlight();
              break;
          case 12:
              codeEditor->highlighter->setChangeValueColor(newColor);
              codeEditor->highlighter->rehighlight();
              break;
          case 13:
              codeEditor->highlighter->setLoopColor(newColor);
              codeEditor->highlighter->rehighlight();
              break;
          case 14:
              codeEditor->highlighter->setCommentColor(newColor);
              codeEditor->highlighter->rehighlight();
              break;
          default:
              break;
          }
          listItems[list->currentRow()-2].second = newColor;
      }
  }
}

void Settings::addListItem(QString text, QColor color,  int character){
    QVariantMap options;
    options.insert( "color" , color );
    QListWidgetItem *item = new QListWidgetItem(awesome->icon(character, options).pixmap(256,256), text);
    list->addItem(item);
}

void Settings::setup(){
    codeEditor->setPlainText("<>+-[],.comment");
    codeEditor->setReadOnly(true);
    codeEditor->setFixedHeight(codeEditor->fontMetrics().height() * 3);
    layout()->addWidget(codeEditor);

    themes->addItem("light");
    themes->addItem("dark");
    themes->addItem("custom");
    if(currentTheme == "light")
        themes->setCurrentItem(themes->item(0));
    else if(currentTheme == "dark")
        themes->setCurrentItem(themes->item(1));
    else
        themes->setCurrentItem(themes->item(2));
    themes->setFixedHeight(themes->sizeHintForRow(0) * themes->count() + 2 * themes->frameWidth());
    layout()->addWidget(themes);
    connect(themes, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(changeTheme()));

    addListItem("Font: " + font_.family(), Qt::gray, fa::font);
    addListItem("Comment Font: " + commentFont_.family(), Qt::gray, fa::font);

    for(std::pair<QString, QColor>& item : listItems ){
        addListItem(item.first, item.second);
    }

    layout()->addWidget(list);
    connect(list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(change()));

    setWindowTitle("Brainfuck IDE - Settings");
    QVariantMap options;
    options.insert( "color" , QColor(187,187,187) );
    setWindowIcon(awesome->icon(fa::wrench, options).pixmap(256,256));
    setAutoFillBackground(true);
    setPalette(listItems[0].second);
}
std::vector<QColor> Settings::getColors(){
    std::vector<QColor> colors;
    for(size_t i=0; i<13; ++i){
        colors.push_back(listItems[i].second);
    }
    return colors;
}
