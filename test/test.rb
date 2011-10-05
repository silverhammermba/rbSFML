require 'test/unit'

begin
  require 'sfml/sfml.so'
  puts "Loaded 'sfml/sfml.so'"
rescue Exception
  begin
    require 'sfml/system.so'
    puts "Loaded 'sfml/system.so'"
  rescue Exception
  else
    $system = true
  end
  begin
    require 'sfml/window.so'
    puts "Loaded 'sfml/window.so'"
  rescue Exception
  else
    $window = true
  end
  begin
    require 'sfml/graphics.so'
    puts "Loaded 'sfml/graphics.so'"
  rescue Exception
  else
    $graphics = true
  end
  begin
    require 'sfml/audio.so'
    puts "Loaded 'sfml/audio.so'"
  rescue Exception
  else
    $audio = true
  end
else
  $system = true
  $window = true
  $graphics = true
  $audio = true
end

warn "Warning: Cannot load System module"   unless $system
warn "Warning: Cannot load Window module"   unless $window
warn "Warning: Cannot load Graphics module" unless $graphics
warn "Warning: Cannot load Audio module"    unless $audio

exit unless $system or $window or $graphics or $audio

if $system
  
end

if $window
  
end

if $graphics
  load "test/graphics/test_color.rb"
  load "test/graphics/test_rect.rb"
end

if $audio
  
end
