
#include <QtCore/QDebug>
#include "sqlserializer.h"

SqlSerializer::SqlSerializer() :StringSerializer ()
{

}

#define CASE_W(o, r) \
    case o: \
        ret.append(r); \
        break;
QString SqlSerializer::escapeString(const QString &str) const
{
//    QString ret;
//    for (int i = 0; i < str.length(); ++i) {
//        switch (str.at(i).cell()) {
//        CASE_W('\\', "\\\\")
//        CASE_W('\r', "\\r")
//        CASE_W('\n', "\\n")
//        CASE_W('\a', "\\a")
//        CASE_W('\b', "\\b")
//        CASE_W('\f', "\\f")
//        CASE_W('\'', "''")
//        CASE_W('\t', "\\t")
//        CASE_W('\v', "\\v")
////        CASE_W('\"', "\\\"")

//        default:
//            ret.append(str.at(i));
//        }
//    }
//    return ret;
    QString ret(str);
    return ret.replace(QStringLiteral("'"), QStringLiteral("''"));
}

QString SqlSerializer::unescapeString(const QString &str) const
{
//    QString ret;
//    for (int i = 0; i < str.length(); ++i) {
//        if (str.at(i) == '\'' && str.at(i + 1) == '\'' && str.length() > i + 1) {
//            ret.append('\'');
//            i++;
//            continue;
//        }
//        if (str.at(i) == '\\' && str.length() > i) {
//            switch (str.at(++i).cell()) {
//            case '\\':
//                ret.append("\\");
//                break;
//            case 'r':
//                ret.append("\r");
//                break;
//            case 'n':
//                ret.append("\n");
//                break;
//            case 'a':
//                ret.append("\a");
//                break;
//            case 'b':
//                ret.append("b");
//                break;
//            case 'f':
//                ret.append("\f");
//                break;
//            case 't':
//                ret.append("\t");
//                break;
//            case 'v':
//                ret.append("\v");
//                break;

//            default:
//                ret.append(str.at(i));
//            }
//        } else {
//            ret.append(str.at(i));
//        }
//    }

//    return ret;
    QString ret(str);
    return ret.replace(QStringLiteral("''"), QStringLiteral("'"));
}
