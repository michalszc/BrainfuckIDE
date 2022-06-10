#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include "codeeditor.h"

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *codeEditor_) : QWidget(codeEditor_), codeEditor(codeEditor_) {}
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    CodeEditor *codeEditor;
};

#endif // LINENUMBERAREA_H
