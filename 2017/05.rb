fname = '05.txt'

class Solution
  @sm = []
  @lg = []
  @size = 0

  def self.add n
    @sm << n
    @lg << n
  end

  def self.sm
    @sm
  end

  def self.lg
    @lg
  end

  def self.size
    @size
  end

  def self.calc_size
    @size = sm.length
  end

  def self.small
    i = count = n = 0
    while i < size do
      count += 1
      n = sm[i]
      sm[i] = sm[i] + 1
      i += n
    end
    count
  end

  def self.large
    i = count = n = 0
    while i < size do
      count += 1
      n = lg[i]
      lg[i] += n >= 3 ? -1 : 1
      i += n
    end
    count
  end

end

File.open(fname, 'r') do |f|
  f.each_line do |line|
    Solution.add(line.to_i)
  end
end

Solution.calc_size
p Solution.small
p Solution.large
