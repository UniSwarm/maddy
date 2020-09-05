#ifndef QMADDY_H
#define QMADDY_H

#include "maddy/parser.h"

#include <QByteArray>

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
        std::stringstream markdownInput(markdownSrc.toStdString());
        std::string htmlOutput = parser->Parse(markdownInput);
        return QByteArray::fromStdString(htmlOutput);
    }

private:
    std::shared_ptr<maddy::ParserConfig> config;
    std::shared_ptr<maddy::Parser> parser;
};
}
#endif // QMADDY_H
