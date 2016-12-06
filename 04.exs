input = with { :ok, file } = File.open( "04_input" ),
             lines = IO.read( file, :all ),
             :ok = File.close( file )
        do
          String.splitter( lines, [ "\n", " " ], trim: true )
          # [ "abc-def-123[abcde]" ... ]
        end

defmodule One do

  def run( input ) do
    input
    |> Stream.map( &parse/1 )
    |> Stream.map( &step/1 )
    |> Stream.filter( &(&1) )
    |> Enum.reduce( fn( x, acc ) -> x + acc end )
  end

  def parse( str ) do
    r_checksum = ~r/[\[](\w+)[\]]/
    [ _, checksum ] = Regex.run  r_checksum, str, captures: :first
    str = Regex.replace r_checksum, str, ""

    [ sector ] = Regex.run( ~r/\d+/, str ) |> Enum.map( &String.to_integer/1 )

    letters = Regex.replace ~r/[\d\-]/, str, ""

    # letters :: str, checksum :: str, sector :: int
    { letters, checksum, sector } 
  end

  def to_checksum( letters ) do
    letters
    |> String.split( "", trim: true )
    |> Enum.group_by( &(&1) )
    |> Enum.map( fn { k, list } -> { k, Enum.count( list ) } end )
    |> Enum.sort_by( fn { _, v } -> v end, &>=/2 )
    |> Enum.take( 5 )
    |> Enum.map( fn { k, _ } -> k end )
    |> Enum.join
  end

  def step( { letters, checksum, sector } ) do 
    if to_checksum( letters ) === checksum do
      sector
    else
      nil
    end
  end

end

input
|> One.run
|> IO.inspect

defmodule Two do

  def run( input ) do 
    input
    |> Stream.map( &step/1 )
    |> Stream.filter( &target?/1 )
    |> Enum.to_list
  end

  def target?( str ), do: Regex.run( ~r/north|pole/, str )

  def step( str ) do
    [ count ] = Regex.run( ~r/\d+/, str ) |> Enum.map( &String.to_integer/1 )

    str
    |> to_charlist
    |> Enum.map( fn char -> cycle( char, count ) end )
    |> to_string
  end

  def cycle( input, _ ) when input === 45, do: 32 # '-' to ' '

  def cycle( input, _ ) when input < 97, do: input # guard for nums

  def cycle( input, count ) do
    input - 97 + count
    |> rem( 26 )
    |> Kernel.+( 97 )
  end

end

# [ "abc-xyz-1", "north-pole-express-26[hello]" ]
input
|> Two.run
|> IO.inspect
