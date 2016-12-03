
# File handler

input = with { :ok, file } = File.open( "01_input" ),
             line = IO.read( file, :line ),
             :ok = File.close( file )
        do
          # normalise "R123, L32, .." to [ { "R", 123 }, { "L", 32 }, .. ]
          String.replace( line, "\n", "" )
          |> String.split( ", " )
          |> Enum.map( fn direction ->
            { dir, val } = String.split_at( direction, 1 )
            { dir, String.to_integer( val ) }
          end )
        end

# One

defmodule One do
  
  def run( instructions ) do
    step instructions, %{ x: 0, y: 0, direction: [ 0, 1 ] }
  end

  defp step( [], result ), do: result

  defp step( [ { "L", amt } | tail ], %{ x: x, y: y, direction: [ a, b ] } ) do
    [ a, b ] = [ -b, a ]
    x = x + a * amt
    y = y + b * amt
    step( tail, %{ x: x, y: y, direction: [ a, b ] } )
  end

  defp step( [ { "R", amt } | tail ], %{ x: x, y: y, direction: [ a, b ] } ) do
    [ a, b ] = [ b, -a ]
    x = x + a * amt
    y = y + b * amt
    %{ x: x, y: y, direction: [ a, b ] }
    step( tail, %{ x: x, y: y, direction: [ a, b ] } )
  end

end

res = One.run input
IO.inspect res
IO.puts abs( res.x ) + abs( res.y )

# Two

defmodule Two do
  
  def run( instructions ) do
    step instructions, %{ x: 0, y: 0, direction: [ 0, 1 ] }, []
  end

  defp step( [], result, visited ), do: { result, visited }

  # TODO refactor the steps function
  
  defp step( [ { "L", amt } | tail ], res, visited ) do
    [ a, b ] = res.direction
    [ a, b ] = [ -b, a ]

    points = 1..amt |> Enum.map( &( { res.x + a * &1, res.y + b * &1 } ) )

    if res = first_member( points, visited ) do
      early_return res
    else
      { x, y } = List.last points
      step tail, %{ x: x, y: y, direction: [ a, b ] }, visited ++ points
    end
  end

  defp step( [ { "R", amt } | tail ], res, visited ) do
    [ a, b ] = res.direction
    [ a, b ] = [ b, -a ]

    points = 1..amt |> Enum.map( &( { res.x + a * &1, res.y + b * &1 } ) )

    if res = first_member( points, visited ) do
      early_return res
    else
      { x, y } = List.last points
      step tail, %{ x: x, y: y, direction: [ a, b ] }, visited ++ points
    end
  end

  defp first_member( [], _ ), do: nil

  defp first_member( subset, list ) do
    [ h | t ] = subset

    if h in list do
      h
    else
      first_member t, list
    end
  end

  defp early_return( { x, y } ), do: { { x, y }, abs( x ) + abs ( y ) }

end

# test = [ { "R", 5 }, { "R", 3 }, { "R", 3 }, { "R", 3 }, { "L", 1 } ]
{ res, other } = Two.run( input )
IO.inspect res
IO.puts other
