# defining the NODE class for each node
# in the BST
class NODE
  # init takes a value x to be set as its value
  # lef and right nill
  def initialize(x)
    @value = x
    @left = nil
    @right = nil
  end

  # a function that can modify all 3 values
  def vals(v, l, r)
    @value = v
    @left = l
    @right = r
  end

  # creating attribtue accessors to modify or access the 3
  # attributes. value, left and right
  attr_accessor(:value, :left, :right)
end

# the set class that uses BST under the hood to store the set
# and its functions
class SET
  # init sets the size to 0 and root to nil
  def initialize
    @size = 0
    @root = nil
  end

  # a class method to create a new set based on the string of
  # comma seperated values passed as string
  def SET.new_set(s)
    # creating the list using eval
    list = eval('[' + s + ']')

    set = SET.new # creating a new set

    # add each element in the
    for e in list
      set.insert e
    end

    set # return the set
  end

  # a method that returns true or false
  # based on whether the value is present in the Set
  # takes one argument supposed to be the value we are
  # searching for
  def has(x)
    # if the root is not nil
    unless @root.nil?
      curr = @root
      prev = nil

      # perform the search by going left or right
      # until we are at null or we find the value
      while !curr.nil?
        prev = curr

        # check if we are at the value
        if curr.value == x
          return true
        end

        if curr.value < x
          curr = curr.right
        else
          curr = curr.left
        end
      end
    end

    # couldn't find the value or root it nil
    false
  end

  # method that inserts a value into the set
  # and updates the size. takes two arguements
  # x = the value to be inserted
  # out = true if we want print statements by this insert
  def insert(x, out = true)
    # if no nodes
    if @root.nil?
      # create a new Node and set it as the root
      @root = NODE.new(x)
    else
      # or start at the root and find the correct place for
      # the value by moving left or right
      curr = @root
      prev = nil # pointer to keep track of current's parent

      while !curr.nil?
        prev = curr

        # check if we stopped at a duplicate
        if curr.value == x
          puts "cannot insert duplicate value #{x}" if out
          return false
        end

        if curr.value < x
          curr = curr.right
        else
          curr = curr.left
        end
      end

      # check where the value is supposed to go
      if prev.value < x
        prev.right = NODE.new(x)
      else
        prev.left = NODE.new(x)
      end
    end

    # increment the size
    @size += 1
    true
  end

  # method to help the to_s method
  # recursively builds and returns the string for the set
  def inorder_rec(node)
    # base condition
    if node.nil?
      return ""
    end

    # if left is nil we insert "" before us
    # or recursively go left to build the string and add a comma
    # then the current node and then same for recursive right
    ((node.left.nil?) ? "" : (inorder_rec(node.left) + ", ")) + node.value.to_s + ((node.right.nil?) ? "" : (", " + inorder_rec(node.right)))
  end

  # method that returns a string representing the set
  def to_s
    # if the set is empty
    if @size == 0
      return "the set is empty"
    end

    # recursively build the string starting at the root
    "{" + inorder_rec(@root) + "}"
  end

  # method to post order recursively add all the nodes
  # from current tree to the result set
  def po_add_all(node, result)
    unless node.nil?
      result.insert(node.value, false) # insert to the result set

      # recursively go left and right
      po_add_all(node.left, result)
      po_add_all(node.right, result)
    end
  end

  # method to perform the union of receiver and
  # and teh argument set
  def union(other)
    # create a new set
    result = SET.new

    # recursively add all values from current
    # set to the result
    po_add_all(@root, result)
    # same for the other set
    po_add_all(other.get_root, result)

    # return the result
    result
  end

  # method to post order recursively perform the intersection
  # of current set and the argument set and post it in the result set
  def po_intersection(node, other, result)
    unless node.nil?
      # if the current node is present in the other
      # set then insert it
      result.insert(node.value, false) if other.has(node.value)

      # recursively travel left adn right
      po_intersection(node.left, other, result)
      po_intersection(node.right, other, result)
    end
  end

  # method to perform the intersection of receiver and
  # and teh argument set
  def intersection(other)
    result = SET.new

    # call teh helper
    po_intersection(@root, other, result)

    result
  end

  # method to deep copy the receiver set and
  # return the copy
  def deep_copy
    # marshalling and unmarshalling
    Marshal.load(Marshal.dump(self))
  end

  # in order recursive application of a lambda l
  def ino_app_l(node, l)
    unless node.nil?
      ino_app_l(node.left, l)

      # print the result of lambda call
      puts l.call(node.value)

      ino_app_l(node.right, l)
    end
  end

  # method to apply the lambda l passed as a string
  # to all elements in the set
  def apply_lambda(l)
    puts "applying the lambda: " + l + " to each element"

    # create the lambda
    l = eval(l)

    # apply and print
    ino_app_l(@root, l)
  end

  # attribute accessors for the size
  attr_reader(:size)

  # protected get root
  protected
  def get_root
    @root
  end
end