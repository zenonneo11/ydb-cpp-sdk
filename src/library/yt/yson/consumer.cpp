#include <ydb-cpp-sdk/library/yt/yson/consumer.h>

#include <src/library/yt/yson_string/string.h>

namespace NYT::NYson {

////////////////////////////////////////////////////////////////////////////////

void IYsonConsumer::OnRaw(const TYsonStringBuf& yson)
{
    OnRaw(yson.AsStringBuf(), yson.GetType());
}

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NYson
