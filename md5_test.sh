#!/bin/bash

exe_test() {
  cmd_to_exe=$1
  expected_output=$2
  nbr_test=$3
  #execute string in cmd_to_exe
  output=$(eval $cmd_to_exe)
  #compare output with expected_output
  if [ "$output" == "$expected_output" ]; then
    echo "Test $nbr_test passed"
  else
    echo "Test $nbr_test failed"
    echo "Expected output: $expected_output"
    echo "Actual output: $output"
    exit 1
  fi
}

cd cmake-build-debug
# Test 1
exe_test "echo \"42 is nice\" | ./ft_ssl md5" "(stdin)= 35f1d6de0302e2086a4e472266efb3a9" 1
# Test 2
exe_test "echo \"42 is nice\" | ./ft_ssl md5 -p" "(\"42 is nice\")= 35f1d6de0302e2086a4e472266efb3a9" 2
# Test 3
exe_test "echo \"Pity the living.\" | ./ft_ssl md5 -q -r" "e20c3b973f63482a778f3fd1869b7f25" 3
# Test 4
echo "And above all," > file
exe_test "./ft_ssl md5 file" "MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a" 4
# Test 5
exe_test "./ft_ssl md5 -r file" "53d53ea94217b259c11a5a2d104ec58a file" 5
# Test 6
exe_test "./ft_ssl md5 -s \"pity those that aren't following baerista on spotify.\"" "MD5 (\"pity those that aren't following baerista on spotify.\") = a3c990a1964705d9bf0e602f44572f5f" 6
# Test 7
exe_test "echo \"be sure to handle edge cases carefully\" | ./ft_ssl md5 -p file" $'(\"be sure to handle edge cases carefully\")= 3553dc7dc5963b583c056d1b9fa3349c\nMD5 (file) = 53d53ea94217b259c11a5a2d104ec58a' 7
# Test 8
exe_test "echo \"some of this will not make sense at first\" | ./ft_ssl md5 file" "MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a" 8
# Test 9\n
exe_test "echo \"but eventually you will understand\" | ./ft_ssl md5 -p -r file" $'(\"but eventually you will understand\")= dcdd84e0f635694d2a943fa8d3905281\n53d53ea94217b259c11a5a2d104ec58a file' 9
# Test 10
exe_test "echo \"GL HF let's go\" | ./ft_ssl md5 -p -s \"foo\" file" $'(\"GL HF let\'s go\")= d1e3cc342b6da09480b27ec57ff243e2\nMD5 (\"foo\") = acbd18db4cc2f85cedef654fccc4a4d8\nMD5 (file) = 53d53ea94217b259c11a5a2d104ec58a' 10
# Test 11
exe_test "echo \"one more thing\" | ./ft_ssl md5 -r -p -s \"foo\" file -s \"bar\"" $'(\"one more thing\")= a0bd1876c6f011dd50fae52827f445f5\nacbd18db4cc2f85cedef654fccc4a4d8 \"foo\"\n53d53ea94217b259c11a5a2d104ec58a file\nft_ssl: md5: -s: No such file or directory\nft_ssl: md5: bar: No such file or directory' 11
# Test 12
exe_test "echo \"just to be extra clear\" | ./ft_ssl md5 -r -q -p -s \"foo\" file" $'just to be extra clear\n3ba35f1ea0d170cb3b9a752e3360286c\nacbd18db4cc2f85cedef654fccc4a4d8\n53d53ea94217b259c11a5a2d104ec58a' 12