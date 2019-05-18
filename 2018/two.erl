-module(two).
-import(helpers, [read/1, print/1]).
-export([main/0, proc/0, match/3]).

main() ->
  Input = read("02.txt"),
  print(solve(one, Input)),
  print(solve(two, Input)).

solve(one, List) ->
  Counted = lists:map(fun count/1, List),
  Filtered = lists:map(
               fun ({0, 0}) -> {0, 0};
                   ({_, 0}) -> {1, 0};
                   ({0, _}) -> {0, 1};
                   ({_, _}) -> {1, 1} end,
               Counted
               ),
  {D, T} = lists:foldl(
    fun({D, T}, {Double, Triple}) -> {D + Double, T + Triple} end,
    {0, 0},
    Filtered),
  D * T;

solve(two, Input) ->
  [A, B] = lists:filter(fun (Str) -> compare(Str, Input) =/= false end, Input),
  common(A, B).

% PART ONE

pred(N) -> fun (_, V) -> V =:= N end.

count(Str) -> count(Str, #{}).
count([H|T], Map) -> count(T, maps:put(H, maps:get(H, Map, 0) + 1, Map));
count([], Map) ->
  Remain2 = maps:to_list(maps:filter(pred(2), Map)),
  Remain3 = maps:to_list(maps:filter(pred(3), Map)),
  {length(Remain2), length(Remain3)}.

% PART TWO

-spec common(string(), string()) -> string().
common(X, Y) -> common(X, Y, []).
common([], [], Out) -> Out;
common([H|T1], [H|T2], Out) -> [H|common(T1, T2, Out)];
common([_X|T1], [_Y|T2], Out) -> common(T1, T2, Out).

-spec diff(string(), string()) -> pos_integer().
% convenience default arg
diff(X, Y) -> diff(X, Y, 0).
% when char is same, continue
diff([X|T1], [X|T2], Count) -> diff(T1, T2, Count);
% when char is different, count++
diff([_X|T1], [_Y|T2], Count) -> diff(T1, T2, Count + 1);
% last char
diff(X, X, Count) -> Count;
diff(_X, _Y, Count) -> Count + 1.

-spec compare(any(), []) -> boolean()
    ; (string(), [string()]) -> {}.
compare(_, []) -> false;
compare(Str, [H|T]) ->
  case diff(Str, H) of
    1 -> {Str, H};
    _ -> compare(Str, T)
  end.

% PART TWO WITH PROCESSES

proc() ->
  Input = read("02.txt"),
  print(with_proc(two, Input)).

with_proc(two, Input) ->
  [spawn(?MODULE, match, [self(), I, Input]) || I <- Input],
  receive
    {A, B} -> common(A, B);
    X -> io:fwrite("Received message no match~p~n", [X])
  end.

match(Recipient, Str, List) ->
  case compare(Str, List) of
    false -> 0;
    Result -> Recipient ! Result
  end.
