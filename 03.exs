input = with { :ok, file } = File.open( "03_input" ),
             lines = IO.read( file, :all ),
             :ok = File.close( file )
        do
          String.splitter( lines, [ "\n", " " ], trim: true )
          |> Enum.map( &String.to_integer/1 )
          # [1, 2, 3, ...]
        end

defmodule One do

  def run( input ) do
    input
    |> Enum.chunk( 3 )
    |> Enum.filter( &is_triangle?/1 )
    |> Enum.count
  end

  def is_triangle?( [ x, y, z ] ) do
    ( x + y ) > z and
    ( x + z ) > y and
    ( y + z ) > x
  end

end

input
|> One.run
|> IO.inspect

defmodule Two do

  def run( input ) do
    input
    |> massage
    |> One.run
  end

  def massage( list ) do
    0..2
    |> Enum.flat_map( &( list |> Enum.drop( &1 ) |> Enum.take_every( 3 ) ) )
  end

end

input |> Two.run |> IO.inspect
