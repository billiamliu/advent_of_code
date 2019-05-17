-module(one).
-export([main/0]).

% id(X) -> X.
% get_all_lines(Device) -> get_all_lines(fun id/1, Device).

main() ->
  Nums = readlines(fun to_int/1, "./01.txt"),
  print(solve(small, Nums)),
  print(solve(big, Nums)).

readlines(F, FileName) ->
    {ok, Device} = file:open(FileName, [read]),
    try get_all_lines(F, Device)
      after file:close(Device)
    end.

get_all_lines(F, Device) ->
  case io:get_line(Device, "") of
    eof -> [];
    Line -> [F(string:trim(Line)) | get_all_lines(F, Device)]
  end.

print(Num) -> io:fwrite("~B~n", [Num]).

to_int(Str) ->
  {Int, []} = string:to_integer(Str),
  Int.

solve(small, Nums) -> lists:sum(Nums);
solve(big, Nums) -> solve(big, sets:new(), Nums, [], 0).

solve(big, Set, InitNums, [], Curr) ->
  solve(big, Set, InitNums, InitNums, Curr);

solve(big, Set, InitNums, [H|T], Curr) ->
  NewNum = Curr + H,
  case sets:is_element(NewNum, Set) of
    true -> NewNum;
    false -> solve(big, sets:add_element(NewNum, Set), InitNums, T, NewNum)
  end.
