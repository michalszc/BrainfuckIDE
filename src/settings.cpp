#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QtAwesome* awesome_, const QColor colors[], const QFont font,  QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    awesome = awesome_;
    font_ = font;
    codeEditor = new CodeEditor;
    codeEditor->setFont(font_);
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

void Settings::change(){
  if ( list->currentItem() == nullptr ) return;
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
  }else{
      QColor newColor = QColorDialog::getColor(QColor(itemValue), this, "Choose color");
      if ( newColor.isValid() ){
          QVariantMap options;
          options.insert( "color" , newColor );
          list->currentItem()->setIcon(awesome->icon(fa::square, options).pixmap(256,256));
          list->currentItem()->setText(itemType+":  "+newColor.name());
          switch(list->currentRow()){
          case 1:
              setPalette(newColor);
              break;
          case 2:
              codeEditor->setBackgroundColor(newColor);
              break;
          case 3:
              codeEditor->setLineNumberAreaColor(newColor);
              break;
          case 4:
              codeEditor->setLineNumberTextColor(newColor);
              break;
          case 5:
              codeEditor->setLineColor(newColor);
              codeEditor->setReadOnly(false);
              codeEditor->cursorPositionChanged();
              codeEditor->setReadOnly(true);
              break;
          default:
              break;
          }
          listItems[list->currentRow()-1].second = newColor;
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
    codeEditor->setPlainText("<>+-[],.");
    codeEditor->setReadOnly(true);
    codeEditor->setFixedHeight( codeEditor->fontMetrics().height() * 3);
    layout()->addWidget(codeEditor);

    addListItem("Font: " + font_.family(), Qt::gray, fa::font);


    for(std::pair<QString, QColor>& item : listItems ){
        addListItem(item.first, item.second);
    }

    layout()->addWidget(list);

    QPushButton *change_button = new QPushButton(this);
    change_button->setText("Change");
    connect(change_button, SIGNAL(clicked()), this, SLOT(change()));
    layout()->addWidget(change_button);

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
