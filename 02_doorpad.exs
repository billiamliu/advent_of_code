# File handler

input = with { :ok, file } = File.open( "02_input" ),
             lines = IO.read( file, :all ),
             :ok = File.close( file )
        do
          # 2D string char list
          String.split( lines, "\n" )
          |> Enum.map( &String.graphemes/1 )
          |> Enum.drop( -1 )
        end

defmodule One do

  def run( input ) do
    input
    |> Enum.scan( { 1, 1 }, &step/2 )
  end

  defp step( [], res ), do: res

  defp step( [ "U" | t ], { x, 0 } ), do: step( t, { x, 0 } )
  defp step( [ "U" | t ], { x, y } ), do: step( t, { x, y - 1 } )

  defp step( [ "D" | t ], { x, 2 } ), do: step( t, { x, 2 } )
  defp step( [ "D" | t ], { x, y } ), do: step( t, { x, y + 1 } )

  defp step( [ "L" | t ], { 0, y } ), do: step( t, { 0, y } )
  defp step( [ "L" | t ], { x, y } ), do: step( t, { x - 1, y } )

  defp step( [ "R" | t ], { 2, y } ), do: step( t, { 2, y } )
  defp step( [ "R" | t ], { x, y } ), do: step( t, { x + 1, y } )

end

input |> One.run |> IO.inspect

defmodule Two do

  defp grid do
    [
      [ nil, nil, 1, nil, nil ],
      [ nil, 2,   3,   4,   nil ],
      [ 5,   6,   7,   8,   9 ],
      [ nil, "A", "B", "C", nil ],
      [ nil, nil, "D", nil, nil ]
    ]
  end

  def run( input ) do
    input
    |> Enum.scan( { 2, 2 }, &step/2 )
  end

  defp step( [], res ), do: res

  defp step( [ "U" | t ], { y, x } ) do
    if y > 0 and grid |> Enum.at( y - 1 ) |> Enum.at( x ) !== nil do
      step( t, { y - 1, x } )
    else
      step( t, { y, x } )
    end
  end

  defp step( [ "D" | t ], { y, x } ) do
    if y < 4 and grid |> Enum.at( y + 1 ) |> Enum.at( x ) !== nil do
      step( t, { y + 1, x } )
    else
      step( t, { y, x } )
    end
  end

  defp step( [ "L" | t ], { y, x } ) do
    if x > 0 and grid |> Enum.at( y ) |> Enum.at( x - 1 ) !== nil do
      step( t, { y, x - 1 } )
    else
      step( t, { y, x } )
    end
  end

  defp step( [ "R" | t ], { y, x } ) do
    if x < 4 and grid |> Enum.at( y ) |> Enum.at( x + 1 ) !== nil do
      step( t, { y, x + 1 } )
    else
      step( t, { y, x } )
    end
  end

end

# "ULLL\nDRU\nDDDDDDDDDDDDRRRRRURUU" |> String.split( "\n" ) |> Enum.map( &String.graphemes/1 )
input
|> Two.run
|> IO.inspect
