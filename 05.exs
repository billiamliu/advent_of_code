input = "uqwqemis"
test = "abc3231929"

defmodule Md5 do

  def run( args ), do: hot( args )

  def hot( { base, num } ) do
    :crypto.hash( :md5 , base <> to_string( num ) ) |> Base.encode16
  end

  def substitute( { _, num } ) do
     "00000substitute" <> to_string( num )
  end

end

defmodule Logger do

  def log( value \\ "start", number \\ "start" ) do
    { _, { hh, mm, ss } } = :calendar.local_time
    { :ok, tm } = Time.new hh, mm, ss
    entry = "#{ tm }, #{ number }, #{ value }"
    IO.puts entry
    write( entry )
  end

  defp write( e ) do
    { :ok, f } = File.open "05_log", [ :append ]
    IO.puts f, e
    :ok = File.close f
  end

end

defmodule One do 

  def run( base ) do
    Logger.log
    step( nil, { base, 0 }, [], 0 )
  end

  # def to_md5( args ), do: Md5.run( args )
  def to_md5( args ) do
    Md5.run( args )
  end

  def step( _, _, results, count ) when count === 8 do
    Enum.join( results )
  end

  def step( "00000" <> str, { base, num }, results, count ) do
    Logger.log( String.first( str ), num )

    results = List.insert_at( results, -1, String.first( str ) )
    next = { base, num + 1 }
    step( to_md5( next ), next, results, count + 1 )
  end

  def step( _, { base, num }, results, count ) do
    next = { base, num + 1 }
    step( to_md5( next ), next, results, count )
  end
  
end

input
|> One.run
|> IO.inspect

