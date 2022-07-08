#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);

    void setChangeValueColor(QColor newChangeValueColor);
    void setMovingPointerColor(QColor newMovingPointerColor);
    void setLoopColor(QColor newLoopColor);
    void setReadColor(QColor newReadColor);
    void setInputColor(QColor newInputColor);
    void setCommentColor(QColor newCommetColor);

    QColor getChangeValueColor() { return changeValueColor; }
    QColor getMovingPointerColor() { return movingPointerColor; }
    QColor getLoopColor() { return loopColor; }
    QColor getReadColor() { return readColor; }
    QColor getInputColor() { return inputColor; }
    QColor getCommentColor() { return commentColor; }

protected:
    void highlightBlock(const QString &text) override;
    void setDefaultColors();

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat changeValueFormat; // + -
    QTextCharFormat movingPointerFormat; // < >
    QTextCharFormat loopFormat; // []
    QTextCharFormat readFormat; // ,
    QTextCharFormat inputFormat; // .
    QTextCharFormat commentFormat;

    QColor changeValueColor;
    QColor movingPointerColor;
    QColor loopColor;
    QColor readColor;
    QColor inputColor;
    QColor commentColor;
};

#endif // HIGHLIGHTER_H
