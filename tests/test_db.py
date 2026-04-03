import subprocess

def run_script(commands):
    result = subprocess.run(
            ["./bin/harborDB", "--test-mode"],
            input = "\n".join(commands)+"\n",
            capture_output= True,
            text = True
            )

    return result.stdout.strip().split("\n")

def test_insert_and_retrieves(): 
    output = run_script(["insert 1 user1 example.com","select", ".exit"])
    expected_output = ["Executed", "(1 user1 example.com)","Executed" ]  
    assert len(expected_output) == len(output), "Unequal lenght of output and expected output."
    for i, o in enumerate(expected_output): 
        assert o == output[i]

def test_error_on_table_full(): 
    input = [f'insert {i} user{i} user{i}.com' for i in range(1700)]
    output = run_script(input)
    assert "Table Full" in output

def test_max_length_string_insert():
    long_username = "a"*32
    long_email = "b"*255
    result = run_script([f"insert 1 {long_username} {long_email}", "select" ,".exit"])
    expected_output =["Executed", f"(1 {long_username} {long_email})", "Executed"]
    assert len(result) == len(expected_output), "Unequal lenght of output and expected output."
    for i, o in enumerate(result) :
        assert expected_output[i] == o
     
def test_long_length_string_insert(): 
    long_username = "a" * 33
    long_email = "b" * 255
    result = run_script([f"insert 1 {long_username} {long_email}", ".exit"])
    assert "String too long" in result

def test_negative_id_insert(): 
    result = run_script(["insert -1 user1 example1.com", ".exit"])
    assert "Id must be positive" in result
