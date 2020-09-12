#ifndef QMADDY_H
#define QMADDY_H

#include "maddy/parser.h"

#include <QByteArray>
#include <QString>

namespace maddy {

class QMaddy
{
public:
    QMaddy()
    {
        config = std::make_shared<maddy::ParserConfig>();
        config->isEmphasizedParserEnabled = true; // default
        config->isHTMLWrappedInParagraph = true; // default

        parser = std::make_shared<maddy::Parser>(config);
    }

    ~QMaddy()
    {
    }

    QByteArray toHtml(QByteArray markdownSrc) const
    {
        QByteArray out;
        std::stringstream markdownInput(markdownSrc.toStdString());
        std::string htmlOutput = parser->Parse(markdownInput);
        out.append("<!DOCTYPE html>");
        out.append("<html lang=\"en\">");
        out.append("<head>");
        out.append("<meta charset=\"utf-8\">");
        if (!_title.isEmpty())
        {
            out.append("<title>" + _title + "</title>");
        }
        if (!_css.isEmpty())
        {
            out.append("<link rel=\"stylesheet\" href=\"" + _css + "\">");
        }
        out.append("</head>");
        out.append("<body>");
        out.append("<div class=\"markdown-body\">\n");
        out.append(QByteArray::fromStdString(htmlOutput));
        out.append("</div>");
        out.append("</body>");
        out.append("</html>");
        return out;
    }

    QString title() const
    {
        return _title;
    }

    void setTitle(const QString &title)
    {
        _title = title;
    }

    QString css() const
    {
        return _css;
    }

    void setCss(const QString &css)
    {
        _css = css;
    }

private:
    std::shared_ptr<maddy::ParserConfig> config;
    std::shared_ptr<maddy::Parser> parser;
    QString _title;
    QString _css;
};
}
#endif // QMADDY_H
