#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    changeValueFormat.setForeground(QColor(14, 184, 190,255)); //Qt::red
    const QString changeValuePatterns[] = {
        QStringLiteral("\\+"),
        QStringLiteral("-")
    };
    for (const QString &pattern : changeValuePatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = changeValueFormat;
        highlightingRules.append(rule);
    }

    movingPointerFormat.setForeground(QColor(238,110,101,255)); //Qt::green
    const QString movingPointerPatterns[] = {
        QStringLiteral("<"),
        QStringLiteral(">")
    };
    for (const QString &pattern : movingPointerPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = movingPointerFormat;
        highlightingRules.append(rule);
    }

    loopFormat.setForeground(QColor(173,186,199,255)); // Qt::cyan
    const QString loopPatterns[] = {
        QStringLiteral("\\["),
        QStringLiteral("]")
    };
    for (const QString &pattern : loopPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = loopFormat;
        highlightingRules.append(rule);
    }

    readFormat.setForeground(QColor(255,165,0,255)); // orange // Qt::darkYellow
    rule.pattern = QRegularExpression(QStringLiteral(","));
    rule.format = readFormat;
    highlightingRules.append(rule);

    inputFormat.setForeground(Qt::yellow); // Qt::yellow
    rule.pattern = QRegularExpression(QStringLiteral("\\."));
    rule.format = inputFormat;
    highlightingRules.append(rule);


    QFont commentFont;
    commentFont.setFamily("Courier");
    commentFont.setItalic(true);
    commentFont.setFixedPitch(true);
    commentFont.setPointSize(12);

    commentFormat.setForeground(Qt::darkGray);
    commentFormat.setFont(commentFont);
    rule.pattern = QRegularExpression(QStringLiteral("([^\\+-<>,\\.\\[\\]]|[0-9:/])"));
    rule.format = commentFormat;
    highlightingRules.append(rule);
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
