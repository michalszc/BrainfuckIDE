#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    setDefaultColors();
    setDefaultCommentFont();
    HighlightingRule rule;

    changeValueFormat.setForeground(changeValueColor);
    const QString changeValuePatterns[] = {
        QStringLiteral("\\+"),
        QStringLiteral("-")
    };
    for (const QString &pattern : changeValuePatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = changeValueFormat;
        highlightingRules.append(rule);
    }

    movingPointerFormat.setForeground(movingPointerColor);
    const QString movingPointerPatterns[] = {
        QStringLiteral("<"),
        QStringLiteral(">")
    };
    for (const QString &pattern : movingPointerPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = movingPointerFormat;
        highlightingRules.append(rule);
    }

    loopFormat.setForeground(loopColor);
    const QString loopPatterns[] = {
        QStringLiteral("\\["),
        QStringLiteral("]")
    };
    for (const QString &pattern : loopPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = loopFormat;
        highlightingRules.append(rule);
    }

    readFormat.setForeground(readColor);
    rule.pattern = QRegularExpression(QStringLiteral(","));
    rule.format = readFormat;
    highlightingRules.append(rule);

    inputFormat.setForeground(inputColor);
    rule.pattern = QRegularExpression(QStringLiteral("\\."));
    rule.format = inputFormat;
    highlightingRules.append(rule);

    commentFormat.setForeground(commentColor);
    commentFormat.setFont(commentFont);
    rule.pattern = QRegularExpression(QStringLiteral("([^\\+-<>,\\.\\[\\]]|[0-9:;/])"));
    rule.format = commentFormat;
    highlightingRules.append(rule);
}

void Highlighter::setDefaultColors(){
    changeValueColor = QColor(14, 184, 190,255);  //Qt::red
    movingPointerColor = QColor(238,110,101,255); //Qt::green
    loopColor = QColor(173,186,199,255); //Qt::cyan
    readColor = QColor(255,165,0,255); // orange // Qt::darkYellow
    inputColor = Qt::yellow;
    commentColor = Qt::darkGray;
}

void Highlighter::setDefaultCommentFont(){
    commentFont.setFamily("Courier");
    commentFont.setItalic(true);
    commentFont.setFixedPitch(true);
    commentFont.setPointSize(12);
}

void Highlighter::setChangeValueColor(QColor newChangeValueColor){
    changeValueColor = newChangeValueColor;
    changeValueFormat.setForeground(changeValueColor);
    highlightingRules[0].format = highlightingRules[1].format = changeValueFormat;
}
void Highlighter::setMovingPointerColor(QColor newMovingPointerColor){
    movingPointerColor = newMovingPointerColor;
    movingPointerFormat.setForeground(movingPointerColor);
    highlightingRules[2].format = highlightingRules[3].format = movingPointerFormat;
}
void Highlighter::setLoopColor(QColor newLoopColor){
    loopColor = newLoopColor;
    loopFormat.setForeground(loopColor);
    highlightingRules[4].format = highlightingRules[5].format = loopFormat;
}
void Highlighter::setReadColor(QColor newReadColor){
    readColor = newReadColor;
    readFormat.setForeground(readColor);
    highlightingRules[6].format = readFormat;
}
void Highlighter::setInputColor(QColor newInputColor){
    inputColor = newInputColor;
    inputFormat.setForeground(inputColor);
    highlightingRules[7].format = inputFormat;
}
void Highlighter::setCommentColor(QColor newCommentColor){
    commentColor = newCommentColor;
    commentFormat.setForeground(commentColor);
    highlightingRules[8].format = commentFormat;
}

void Highlighter::setCommentFont(QFont newFont){
    commentFont = newFont;
    commentFormat.setFont(commentFont);
    highlightingRules[8].format = commentFormat;
}

void Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
