require './set_class'

# the class with the main I/O program
class Project1

  # the class method main
  def Project1.main
    # print welcome
    puts "Welcome to the Set Calculator"

    # initialize the sets
    puts "...initializing X, Y, Z\n\n"
    x = SET.new
    y = SET.new
    z = SET.new

    # take the command and chomp the newline
    puts "please enter the command:"
    command = gets.chomp

    # for file I/O
    # file = File.open("input.txt")
    # file_data = file.readlines.map(&:chomp)

    # while q is not entered as the command
    while command != "q"
    # for command in file_data
      # puts "please enter the command: " + command
      # cases for the command based on the first char
      case command[0]
      when 'X' then
        x = SET.new_set(command[1..-1])
      when 'Y' then
        y = SET.new_set(command[1..-1])
      when 'Z' then
        z = SET.new_set(command[1..-1])
      when 'a' then
        x.insert(eval(command[1..-1]))
      when 'r' then
        # switch the pointers for the
        # x,y,z sets using a temp
        temp = z
        z = y
        y = x
        x = temp
      when 's' then
        # switch the pointers for x,y sets
        # using temp
        temp = x
        x = y
        y = temp
      when 'u' then
        # take the union and put it in x
        x = x.union(y)
      when 'i' then
        # take the intersection and put it in x
        x = x.intersection(y)
      when 'c' then
        # take the deep copy of x and put it in y
        y = x.deep_copy
      when 'l' then
        # apply the lambda on x
        x.apply_lambda(command[1..-1])
      when 'q' then
        # redundant quit for file I/O
        break
      else
        puts "please enter a known command or 'q' to quit"
      end

      # print the sets
      puts "X is: #{x}\n"
      puts "Y is: #{y}\n"
      puts "Z is: #{z}\n\n"

      puts "please enter the command:"
      command = gets.chomp
    end

    # file.close
    puts "..quitting"
  end
end

# run the program loop
Project1.main