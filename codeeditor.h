#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QPalette>
#include <QPainter>
#include <QTextBlock>
#include <QVBoxLayout>


class CodeEditor: public QPlainTextEdit
{
    Q_OBJECT
public:
    CodeEditor(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    void setLineNumberAreaColor(QColor newColor);
    void setLineNumberTextColor(QColor newColor);
    void setLineColor(QColor newColor);
    void setBackgroundColor(QColor newColor);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea;
    QColor lineNumberAreaColor;
    QColor lineNumberTextColor;
    QColor lineColor;
    QColor backgroundColor;
};

#endif // CODEEDITOR_H
