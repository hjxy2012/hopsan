/*-----------------------------------------------------------------------------

 Copyright 2017 Hopsan Group

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 The full license is available in the file GPLv3.
 For details about the 'Hopsan Group' or information about Authors and
 Contributors see the HOPSANGROUP and AUTHORS files that are located in
 the Hopsan source code root directory.

-----------------------------------------------------------------------------*/

#ifndef HIGHLIGHTINGUTILITIES_H
#define HIGHLIGHTINGUTILITIES_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QColor>

class XmlHighlighter : public QSyntaxHighlighter
{
public:
    XmlHighlighter(QTextDocument* parent);

    enum HighlightType
    {
        SyntaxChar,
        ElementName,
        Comment,
        AttributeName,
        AttributeValue,
        Error,
        Other
    };

    void setHighlightColor(HighlightType type, QColor color, bool foreground = true);
    void setHighlightFormat(HighlightType type, QTextCharFormat format);

protected:
    void highlightBlock(const QString& rstrText);
    int  processDefaultText(int i, const QString& rstrText);

private:
    QTextCharFormat mSyntaxChar;
    QTextCharFormat mElementName;
    QTextCharFormat mComment;
    QTextCharFormat mAttributeName;
    QTextCharFormat mAttributeValue;
    QTextCharFormat mError;
    QTextCharFormat mOther;

    enum ParsingState
    {
        NoState = 0,
        ExpectElementNameOrSlash,
        ExpectElementName,
        ExpectAttributeOrEndOfElement,
        ExpectEqual,
        ExpectAttributeValue
    };

    enum BlockState
    {
        NoBlock = -1,
        InComment,
        InElement
    };

    ParsingState state;
};


class CppHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    CppHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> mHighlightingRules;

    QRegExp mCommentStartExpression;
    QRegExp mCommentEndExpression;

    QTextCharFormat mKeywordFormat;
    QTextCharFormat mHopsanKeywordFormat;
    QTextCharFormat mPreProcessorFormat;
    QTextCharFormat mClassFormat;
    QTextCharFormat mSingleLineCommentFormat;
    QTextCharFormat mMultiLineCommentFormat;
    QTextCharFormat mQuotationFormat;
    QTextCharFormat mTagFormat;
    QTextCharFormat mFunctionFormat;
};


#endif // HIGHLIGHTINGUTILITIES_H
