-module(helpers).
-export([read/1, print_int/1, str_to_int/1, print/1]).

read(FileName) ->
  {ok, Device} = file:open(FileName, [read]),
  try get_all_lines(Device)
  after file:close(Device)
  end.

get_all_lines(Device) ->
  case io:get_line(Device, "") of
    eof -> [];
    Line -> [string:trim(Line) | get_all_lines(Device)]
  end.

print(Str) -> io:fwrite("~s~n", [Str]).
print_int(Num) -> io:fwrite("~B~n", [Num]).
str_to_int(Str) -> {Int, _} = string:to_integer(Str), Int.
