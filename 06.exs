input = with { :ok, f} = File.open( "06_input" ),
             lines = IO.read( f, :all ),
             :ok = File.close( f )
        do
             lines
             |> String.split( "\n", trim: true )
        end

defmodule One do

  def run( input ) do
    input
    |> Enum.map( fn line -> line |> String.graphemes |> Enum.with_index end )
    |> step( [] )
  end

  def format( x, results \\ [] )
  def format( [], results ), do: Enum.join( results, "" )
  def format( [ h | t ], results ) do
    { res, _ } = h
    |> Map.to_list
    |> Enum.sort( &sort/2 )
    |> List.first

    format( t, results ++ [res] )
  end

  def sort( { p_ltr, p_count }, { ltr, count } ) when p_count === count do
    p_ltr < ltr
  end

  def sort( { _, p_count }, { _, count } ) do
    p_count > count
  end

  def step( [], mem ) do
    format( mem )
  end

  def step( list, [] ) do
    [ h | _ ] = list

    mem = 1..Enum.count( h ) |> Enum.map( fn _ -> %{} end )
    
    step( list, mem )
  end

  def step( [ h | t ], mem ) do
    mem = Enum.reduce( h, mem, fn
                   entry, acc -> update( acc, entry )
    end )

    step( t, mem )
  end

  def update( mem, { ltr, idx } ) do
    slot = Enum.at( mem, idx )

    { _, slot } = Map.get_and_update( slot, ltr, fn
                              nil -> { nil, 1 }
                              count -> { count, count + 1 }
    end )

    List.replace_at( mem, idx, slot )
  end

end

input
|> One.run
|> IO.inspect
