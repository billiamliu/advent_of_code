class Scanner
  attr_reader :location

  def initialize(location, range)
    @location, @range = location, range
  end

  def reset!
    @position = 0
  end

  def tick
    change_direction if position == 0 || position == range - 1
    move
  end

  def hit?(packet)
    packet.location == location && position == 0
  end

  def severity
    location * range
  end

  private

  def move
    @position = position + direction
    @position = 0 if position < 0
    @position = range if position > range
  end

  def position
    @position ||= 0
  end

  def direction
    @direction ||= -1
  end

  def change_direction
    @direction = direction * -1
  end

  def range
    @range
  end
end

class Packet
  attr_reader :location

  def tick
    move
  end

  def location
    @location ||= -1
  end

  private

  def move
    @location = location + 1
  end
end

class Firewall
  def initialize(depth, scanners)
    @depth, @scanners = depth, scanners
  end

  def simulate(packet)
    score = 0
    while packet.location < depth do
      packet.send :tick
      scanners.each do |scanner|
        if scanner.hit?(packet)
          score = score + scanner.severity
        end
        scanner.send :tick
      end
    end
    score
  end

  private

  def depth
    @depth
  end

  def scanners
    @scanners
  end
end

contents = File.read('13.txt')
contents = contents.split("\n")
scanners = contents.map do |line|
  l = line.match(/(\d+): (\d+)/)
  Scanner.new(l[1].to_i, l[2].to_i)
end
depth = scanners.last.location + 1

def part1(depth, scanners)
  packet = Packet.new
  firewall = Firewall.new(depth, scanners)
  puts firewall.simulate(packet)
end

part1 depth, scanners
