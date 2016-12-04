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
