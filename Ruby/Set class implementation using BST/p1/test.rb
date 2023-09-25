require './set_class'
require 'test/unit'

class TEST_SET < Test::Unit::TestCase
  def test_empty
    x = SET.new

    assert_equal(x.size,0)
  end

  def test_newset_has
    x = SET.new_set("5,7,3,4,2,8,6,1")

    arr = [1,2,3,4,5,6,7,8]

    for e in arr
      assert_equal(x.has(e),true)
    end

    assert_equal(x.size, arr.size)
  end

  def test_newset_has2
    arr = Array.new(500) {rand(-1000..1000)}

    x = SET.new_set(arr.to_s[1..-2])

    for e in arr
      assert_equal(x.has(e),true)
    end
  end

  def test_newset_has3
    arr = Array.new(50) {rand(-100..100)}

    x = SET.new_set(arr.to_s[1..-2])

    for e in arr
      assert_equal(x.has(e),true)
    end

    for i in 1..100
      r = rand(-100..100)
      assert_equal(arr.include?(r), x.has(r))
    end
  end

  def test_newset_has4_float
    arr = Array.new(100) {rand(-1000.0..1000.0)}

    x = SET.new_set(arr.to_s[1..-2])

    for e in arr
      assert_equal(x.has(e),true)
    end

    for i in 1..100
      r = rand(-1000.0..1000.0)
      assert_equal(arr.include?(r), x.has(r))
    end
  end

  def test_insert1
    arr = Array.new(500) {rand(-1000.0..1000.0)}

    x = SET.new

    for e in arr
      x.insert(e, false)
    end

    for e in arr
      assert_equal(x.has(e),true)
    end

    for i in 1..100
      r = rand(-1000.0..1000.0)
      assert_equal(arr.include?(r), x.has(r))
    end
  end

  def test_insert2
    x = SET.new
    arr = Array.new(500) {rand(-1000.0..1000.0)}

    for e in arr
      assert_equal(x.insert(e, false), true)
    end

    ts = x.size

    for e in arr
      assert_equal(x.insert(e, false), false)
    end

    assert_equal(ts, x.size)
  end

  def test_insert3
    x = SET.new
    y = Set.new
    arr = Array.new(500) {rand(-1000.0..1000.0)}

    for e in arr
      assert_equal(x.insert(e, false), true)
      y << e
    end

    assert_equal(x.size, y.size)

    for e in arr
      assert_equal(x.insert(e, false), false)
    end

    assert_equal(x.size, y.size)
  end

  def test_insert4
    arr = Array.new(500) {rand(-1000.0..1000.0)}
    x = SET.new
    y = Set.new

    for e in arr
      x.insert(e, false)
      y << e
    end

    for e in arr
      assert_equal(x.has(e),true)
    end

    for i in 1..1000
      r = rand(-1000.0..1000.0)
      assert_equal(y.include?(r), x.has(r))
    end

    assert_equal(y.size, x.size)
  end

  def test_tos
    arr = Array.new(500) {rand(-1000.0..1000.0)}
    x = SET.new

    for e in arr
      x.insert(e, false)
    end

    s = "[" + x.to_s[1..-2] + "]"

    assert_equal(s, arr.sort.uniq.to_s)
  end

  def test_union1
    arr = Array.new(500) {rand(-1000..1000)}
    arr2 = Array.new(500) {rand(-1000..1000)}
    x = SET.new
    y = SET.new

    for e in arr
      x.insert(e, false)
    end

    for e in arr2
      y.insert(e, false)
    end

    z = x.union(y)

    for e in arr
      assert_true(z.has(e))
    end

    for e in arr2
      assert_true(z.has(e))
    end
  end

  def test_union2
    x = SET.new
    y = SET.new

    arr = Array.new(100) {rand(-2000..-1000)}
    arr2 = Array.new(100) {rand(1000..2000)}

    for e in arr
      x.insert(e, false)
    end

    for e in arr2
      y.insert(e, false)
    end

    z = x.union(y)

    for e in arr
      assert_true(z.has(e))
    end

    for e in arr2
      assert_true(z.has(e))
    end

    for e in arr2
      assert_false(x.has(e))
      assert_true(y.has(e))
    end

    for e in arr
      assert_false(y.has(e))
      assert_true(x.has(e))
    end

    assert_false(x.equal?(z))
    assert_false(y.equal?(z))
    assert_equal(arr.uniq.size + arr2.uniq.size, z.size)
    assert_equal(arr.uniq.size, x.size)
    assert_equal(arr2.uniq.size, y.size)
  end

  def test_inter1
    x = SET.new
    y = SET.new
    z = Set.new
    z2 = Set.new

    arr = Array.new(500) {rand(-1000..1000)}
    arr2 = Array.new(500) {rand(-1000..1000)}

    for e in arr
      x.insert(e, false)
      z << e
    end

    for e in arr2
      y.insert(e, false)
      z2 << e
    end

    assert_equal(z.size, x.size)
    assert_equal(z2.size, y.size)

    z = z & z2
    t = x.intersection(y)

    assert_equal(z.size, t.size)

    for e in arr
      assert_equal(z.include?(e), t.has(e))
    end

    for e in arr2
      assert_equal(z.include?(e), t.has(e))
    end

    for i in 1..1000
      r = rand(-1000..1000)
      assert_equal(z.include?(r), t.has(r))
    end

    assert_false(t.equal?(x))
    assert_false(t.equal?(y))
  end

  def test_inter3
    x = SET.new
    y = SET.new
    z = Set.new
    z2 = Set.new

    arr = Array.new(5000) {rand(-10000..10000)}
    arr2 = Array.new(5000) {rand(-10000..10000)}

    for e in arr
      x.insert(e, false)
      z << e
    end

    for e in arr2
      y.insert(e, false)
      z2 << e
    end

    assert_equal(z.size, x.size)
    assert_equal(z2.size, y.size)

    z = z & z2
    t = x.intersection(y)

    assert_equal(z.size, t.size)

    for e in arr
      assert_equal(z.include?(e), t.has(e))
    end

    for e in arr2
      assert_equal(z.include?(e), t.has(e))
    end

    for i in 1..10000
      r = rand(-10000..10000)
      assert_equal(z.include?(r), t.has(r))
    end

    assert_false(t.equal?(x))
    assert_false(t.equal?(y))
  end

  def test_inter4
    x = SET.new
    y = SET.new
    z = Set.new
    z2 = Set.new

    arr = Array.new(500) {rand(-1000.0..1000.0)}
    arr2 = Array.new(500) {rand(-1000.0..1000.0)}

    for e in arr
      x.insert(e, false)
      z << e
    end

    for e in arr2
      y.insert(e, false)
      z2 << e
    end

    assert_equal(z.size, x.size)
    assert_equal(z2.size, y.size)

    z = z & z2
    t = x.intersection(y)

    assert_equal(z.size, t.size)

    for e in arr
      assert_equal(z.include?(e), t.has(e))
    end

    for e in arr2
      assert_equal(z.include?(e), t.has(e))
    end

    for i in 1..1000
      r = rand(-1000.0..1000.0)
      assert_equal(z.include?(r), t.has(r))
    end


    assert_false(t.equal?(x))
    assert_false(t.equal?(y))
  end

  def test_inter2
    x = SET.new
    y = SET.new

    arr = Array.new(100) {rand(-2000..-1000)}
    arr2 = Array.new(100) {rand(1000..2000)}

    for e in arr
      x.insert(e, false)
    end

    for e in arr2
      y.insert(e, false)
    end

    z = x.intersection(y)

    assert_equal(z.size, 0)

    for e in arr2
      assert_false(z.has(e))
      assert_false(x.has(e))
      assert_true(y.has(e))
    end

    for e in arr
      assert_false(z.has(e))
      assert_false(y.has(e))
      assert_true(x.has(e))
    end

    assert_false(x.equal?(z))
    assert_false(y.equal?(z))
    assert_equal(arr.uniq.size, x.size)
    assert_equal(arr2.uniq.size, y.size)
  end

  def test_deepcopy1
    x = SET.new_set("55,33,12,67,89,34,101")
    y = x.deep_copy

    assert_equal(y.size, x.size)
    assert_equal(y.to_s, x.to_s)
    assert_false(x.equal?(y))

    x.insert(99)

    assert_false(y.has(99))

    y.insert(999)

    assert_false(x.has(999))

    z = y.deep_copy

    assert_equal(z.size, y.size)
    assert_equal(y.to_s, z.to_s)
    assert_false(z.equal?(y))

    z.insert(9898)

    assert_false(y.has(9898))

    y.insert(909)

    assert_false(z.has(909))
  end

  def test_lambda1
    x = SET.new_set("5,3,6,2,7,4,8,1")
    l = "lambda {|x| x**2}"

    puts "should be 1, 4, 9, 16, 25, 36, 49, 64"
    x.apply_lambda(l)
  end

  def test_lambda2
    x = SET.new_set("5,3,6,2,7,4,8,11")
    l = "->(x) {x**2}"

    puts "should be 4, 9, 16, 25, 36, 49, 64, 121"
    x.apply_lambda(l)
  end

  # def test_lambda_error
  #   x = SET.new_set("5,3,6,2,7,4,8,11")
  #   l = "-> {'hi'}"
  #
  #   x.apply_lambda(l)
  # end
end