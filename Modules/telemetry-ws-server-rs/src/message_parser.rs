use std::str::Chars;

use state_machine_rs::{StateMachine, StateMachineError};

use crate::message_parser::commands::OpenCommandParams;

use self::commands::{Commands, ConvertOptionsCommandParams,ConvertCommandParams, CloseCommandParams, GenerateSetupParam};
use self::commands::Commands::{Open,NotInitialized,ConvertOptions,Close};

mod commands;

#[derive(PartialEq)]
enum Keywords {
    ConvertKeyword,
    OptionKeyword,
    File(String),
    String(String),
    OpenKeyword,
    IntoKeyword,
    CloseKeyword,
    RecordKeyword,
    GenerateKeyword,
    SetupKeyword,
    JsonStringKeyword(String),
    Number(i32)
}
pub fn parse(str:&str)->Result<Commands, String>{
    let command_chars = str.chars();
    let parse_result = parseToken(command_chars);

    //let sm:StateMachine<Keywords> = StateMachine::new();

    match parse_result{
        Ok(tokens) => {
            if let Some(token) = tokens.get(0) {
                match token {
                    Keywords::ConvertKeyword => convert_keyword(tokens, 0),
                    Keywords::OpenKeyword => open_keyword(tokens, 0),
                    Keywords::CloseKeyword => close_keyword(tokens, 0),
                    Keywords::GenerateKeyword => generateKeyword(tokens,0),
                    _ => Err("Right Command not found".to_string())
                }
            } else {
                Err("Tokens is empty".to_string())
            }
            /*
            for token in tokens {

            }
             */
        }
        Err(message) => return Err(message)
    }
    //for char in command_chars{
    //}
}

fn convert_keyword(keywords: Vec<Keywords>,index:i32)->Result<Commands, String>{
    //let mut ret = OpenCommandParams{file:"".to_string()};
    let second = keywords.get(1);
    if let Some(value) = second {
        if let Option = value{
            let mut ret = ConvertOptionsCommandParams{file:"".to_string()};
            let third = keywords.get(2);
            if let Some(file_keyword) = third {
                if let Keywords::File(file_content) = file_keyword{
                    ret.file = file_content.clone();
                } else if let Keywords::String(str_content) = file_keyword {
                    ret.file = str_content.clone();
                } else {
                    return Err("no valid file given".to_string());
                }
            } else {
                return Err("Could not retrieve file from command".to_string());
            }
            return Ok(ConvertOptions(ret));
        } else {
            let mut ret = ConvertCommandParams{config_file:None,configs:None,converter:"".to_string(),from_file: "".to_string(),to_file:"".to_string()};
            if let Keywords::File(file) = value {
                ret.from_file = file.clone();
            } else if let Keywords::String(s) = value{
                ret.from_file = s.clone();
            }
        }
    }
    
    Err("Method Not implemented".to_string())
}

fn open_keyword(keywords:Vec<Keywords>,index:i32)->Result<Commands, String>{
    let mut ret = OpenCommandParams{file:"".to_string()};
    if keywords.len() > 2 {
        return Err("Too Many tokens".to_string());
    }
    let first = keywords.get(0);
    let second = keywords.get(1);
    if let Some(a) = first{
        if Keywords::OpenKeyword != *a{
            return Err("Open should start with Keyword OPEN".to_string());
        }
    }
    if let Some(a) = second {
        if let Keywords::File(file) = a {
            ret.file = (*file).clone();
        } else if let Keywords::String(s) = a{
            ret.file = (*s).clone();
        } else {
            return Err("file Parameter is neither a file nor a string".to_string());
        }
    }
    Ok(Open(ret))
}
fn close_keyword(keywords:Vec<Keywords>,index:i32)->Result<Commands, String>{
    let mut ret = CloseCommandParams{file:"".to_string()};
    if keywords.len() > 2 {
        return Err("Too Many tokens".to_string());
    }
    let first = keywords.get(0);
    let second = keywords.get(1);
    if let Some(a) = first{
        if Keywords::CloseKeyword != *a{
            return Err("Open should start with Keyword OPEN".to_string());
        }
    }
    if let Some(a) = second {
        if let Keywords::File(file) = a {
            ret.file = (*file).clone();
        } else if let Keywords::String(s) = a{
            ret.file = (*s).clone();
        } else {
            return Err("file Parameter is neither a file nor a string".to_string());
        }
    }
    Ok(Close(ret))
}
fn generateKeyword(keywords:Vec<Keywords>,index:i32)->Result<Commands,String>{
    //let mut ret = GenerateSetupParam{}
    let first = keywords.get(0);
    let second = keywords.get(1);
    let thirdGame = keywords.get(2);
    let fourthCar = keywords.get(3);
    let fivethTrack = keywords.get(4);

    if let Some(a) = first{
        if Keywords::GenerateKeyword != *a{
            return Err("Generate Setup should start with Keyword Generate".to_string());
        }
    }
    if let Some(a) = second {
        if Keywords::SetupKeyword != *a{
            return Err("Generate Setup should have setup as second keyword".to_string());
        }
    }
    let mut ret = GenerateSetupParam{car:"".to_string(),game:"".to_string(),track:"".to_string()};
    if let Some(game) = thirdGame{
        if let Keywords::String(game_str) = game{
            ret.game = game_str.clone();
        } else {
            return Err("game Param is not a String".to_string());
        }
    }
    if let Some(car) = fourthCar{
        if let Keywords::String(car_str) = car{
            ret.car = car_str.clone();
        } else {
            return Err("car Param is not a String".to_string());
        }
    }
}

fn parseToken(command_chars:Chars)->Result<Vec<Keywords>,String>{
    let mut ret:Vec<Keywords> = Vec::new();
    
    let mut sm:StateMachine<char> = StateMachine::new();

    let start_state = sm.add_state(None);
    let c_state = sm.add_state(None);
    let cl_state = sm.add_state(None);
    let clo_state = sm.add_state(None);
    let clos_state = sm.add_state(None);
    let close_state = sm.add_state(None);
    let co_state = sm.add_state(None);
    let con_state = sm.add_state(None);
    let conv_state = sm.add_state(None);
    let conve_state = sm.add_state(None);
    let conver_state = sm.add_state(None);
    let convert_state = sm.add_state(None);
    let o_state = sm.add_state(None);
    let op_state = sm.add_state(None);
    let ope_state = sm.add_state(None);
    let open_state = sm.add_state(None);
    let opt_state = sm.add_state(None);
    let opti_state = sm.add_state(None);
    let optio_state = sm.add_state(None);
    let option_state = sm.add_state(None);
    let r_state = sm.add_state(None);
    let re_state = sm.add_state(None);
    let rec_state = sm.add_state(None);
    let reco_state = sm.add_state(None);
    let recor_state = sm.add_state(None);
    let record_state = sm.add_state(None);
    let i_state = sm.add_state(None);
    let in_state = sm.add_state(None);
    let int_state = sm.add_state(None);
    let into_state = sm.add_state(None);
    let g_state = sm.add_state(None);
    let ge_state = sm.add_state(None);
    let gen_state = sm.add_state(None);
    let gene_state = sm.add_state(None);
    let gener_state = sm.add_state(None);
    let genera_state = sm.add_state(None);
    let generat_state = sm.add_state(None);
    let generate_state = sm.add_state(None);
    let s_state = sm.add_state(None);
    let se_state = sm.add_state(None);
    let set_state = sm.add_state(None);
    let setu_state = sm.add_state(None);
    let setup_state = sm.add_state(None); 
    let string_start = sm.add_state(None);
    let string_middle = sm.add_state(None);
    let string_end = sm.add_state(None);
    let number = sm.add_state(None);
    let number_end = sm.add_state(None);
    let json_string = sm.add_state(None);
    let json_string_end = sm.add_state(None);
    let windows_hard_drive = sm.add_state(None);
    let file_state = sm.add_state(None);
    let file_ending_state = sm.add_state(None);
    let command_end = sm.add_state(None);

    sm.add_transition(start_state, start_state, Box::new(|c,_b|(*c) == ' '), Box::new(|_c,b|b.clear()));
    sm.add_transition(start_state, command_end, Box::new(|c,_b|(*c) == ';'), Box::new(|_c,_b|()));
    sm.add_transition(start_state,c_state,Box::new(|c,_buffer|(*c)=='c'||(*c)=='C'),Box::new(|_c,_buffer|()));

    sm.add_transition(c_state,cl_state,Box::new(|c,_buffer|(*c)=='l'||(*c)=='L'),Box::new(|_c,_buffer|()));
    sm.add_transition(cl_state,clo_state,Box::new(|c,_buffer|(*c)=='o'||(*c)=='O'),Box::new(|_c,_buffer|()));
    sm.add_transition(clo_state,clos_state,Box::new(|c,_buffer|(*c)=='s'||(*c)=='S'),Box::new(|_c,_buffer|()));
    sm.add_transition(clos_state,close_state,Box::new(|c,_buffer|(*c)=='e'||(*c)=='E'),Box::new(|_c,_buffer|()));

    sm.add_transition(c_state,co_state, Box::new(|c,_buffer|(*c)=='o'||(*c)=='O'), Box::new(|_c,_buffer|()));
    sm.add_transition(co_state,con_state, Box::new(|c,_buffer|(*c)=='n'||(*c)=='N'), Box::new(|_c,_buffer|()));
    sm.add_transition(con_state,conv_state, Box::new(|c,_buffer|(*c)=='v'||(*c)=='V'), Box::new(|_c,_buffer|()));
    sm.add_transition(conv_state,conve_state, Box::new(|c,_buffer|(*c)=='e'||(*c)=='E'), Box::new(|_c,_buffer|()));
    sm.add_transition(conve_state,conver_state, Box::new(|c,_buffer|(*c)=='r'||(*c)=='R'), Box::new(|_c,_buffer|()));
    sm.add_transition(conver_state,convert_state, Box::new(|c,_buffer|(*c)=='t'||(*c)=='T'), Box::new(|_c,_buffer|()));

    sm.add_transition(op_state,opt_state,Box::new(|c,_b|(*c) == 'T' ||(*c) == 't'),Box::new(|_c,_b|()));
    sm.add_transition(opt_state,opti_state, Box::new(|c,_b|(*c) == 'i' ||(*c) == 'I'),Box::new(|_c,_b|()));
    sm.add_transition(opti_state,optio_state,Box::new(|c,_b|(*c) == 'o' || (*c) == 'O'),Box::new(|_c,_b|()));
    sm.add_transition(optio_state,option_state,Box::new(|c,_b|(*c) == 'n'||(*c) == 'N'),Box::new(|_c,_b|()));

    sm.add_transition(start_state,r_state,Box::new(|c,_b|(*c) == 'r'||(*c) == 'R'),Box::new(|_c,_b|()));
    sm.add_transition(r_state,re_state,Box::new(|c,_b|(*c)=='e'||(*c) == 'E'),Box::new(|_c,_b|()));
    sm.add_transition(re_state,rec_state,Box::new(|c,_b|(*c) == 'c'||(*c)=='C'),Box::new(|_c,_b|()));
    sm.add_transition(rec_state,reco_state,Box::new(|c,_b|(*c)=='o'||(*c)=='O'),Box::new(|_c,_b|()));
    sm.add_transition(reco_state,recor_state,Box::new(|c,_b|(*c) == 'r'||(*c)=='R'),Box::new(|_c,_b|()));
    sm.add_transition(recor_state,record_state,Box::new(|c,_b|(*c)=='d'||(*c)=='D'),Box::new(|_c,_b|()));

    sm.add_transition(start_state, o_state, Box::new(|c,_b|(*c) == 'o' || (*c) == 'O'), Box::new(|_c,_b|()));
    sm.add_transition(o_state,op_state,Box::new(|c,_b|(*c) == 'p'||(*c) == 'P'),Box::new(|_c,_b|()));
    sm.add_transition(op_state,ope_state,Box::new(|c,_b|(*c) == 'e'||(*c) == 'E'),Box::new(|_c,_b|()));
    sm.add_transition(ope_state,open_state,Box::new(|c,_b|(*c) == 'n'||(*c) == 'N'),Box::new(|_c,_b|()));

    sm.add_transition(start_state,i_state,Box::new(|c,_b|(*c) == 'i' || (*c) == 'I'),Box::new(|_c,_b|()));
    sm.add_transition(i_state,in_state,Box::new(|c,_b|(*c) == 'n' ||(*c) == 'N'),Box::new(|_c,_b|()));
    sm.add_transition(in_state,int_state, Box::new(|c,_b|(*c) == 't'||(*c) == 'T'), Box::new(|_c,_b|()));
    sm.add_transition(int_state,into_state,Box::new(|c,_b|(*c) == 'o'||(*c) == 'O'),Box::new(|_c,_b|()));

    sm.add_transition(start_state,g_state, Box::new(|c,_b|(*c) == 'g'|| (*c) =='G'), Box::new(|_c,_b|()));
    sm.add_transition(g_state,ge_state,Box::new(|c,_b|(*c) == 'e'||(*c) == 'E'),Box::new(|_c,_b|()));
    sm.add_transition(ge_state,gen_state,Box::new(|c,_b|(*c) == 'n'||(*c) == 'N'),Box::new(|_c,_b|()));
    sm.add_transition(gen_state,gene_state,Box::new(|c,_b|(*c) == 'e'||(*c) == 'E'),Box::new(|_c,_b|()));
    sm.add_transition(gene_state,gener_state, Box::new(|c,_b|(*c)=='r'||(*c)=='R'),Box::new(|_c,_b|()));
    sm.add_transition(gener_state,genera_state,Box::new(|c,_b|(*c)=='a'||(*c)=='A'),Box::new(|_c,_b|()));
    sm.add_transition(genera_state,generat_state,Box::new(|c,_b|(*c)=='t'||(*c) =='T'),Box::new(|_c,_b|()));
    sm.add_transition(generat_state,generate_state,Box::new(|c,_b|(*c)=='e'||(*c)=='E'),Box::new(|_c,_b|()));

    sm.add_transition(start_state,s_state,Box::new(|c,_b|(*c)=='s'||(*c)=='S'),Box::new(|_c,_b|()));
    sm.add_transition(s_state,se_state,Box::new(|c,_b|(*c)=='e'||(*c)=='E'),Box::new(|_c,_b|()));
    sm.add_transition(se_state,set_state,Box::new(|c,_b|(*c) == 't'||(*c)=='T'),Box::new(|_c,_b|()));
    sm.add_transition(set_state,setu_state,Box::new(|c,_b|(*c)=='u'||(*c)=='U'),Box::new(|_c,_b|()));
    sm.add_transition(setu_state,setup_state,Box::new(|c,_b|(*c)=='p'||(*c)=='P'),Box::new(|_c,_b|()));

    sm.add_transition(start_state,json_string,Box::new(|c,_b|(*c) == '{'),Box::new(|_c,_b|()));
    sm.add_transition(json_string,json_string,Box::new(|c,_b|(*c)!='}'),Box::new(|_c,_b|()));
    sm.add_transition(json_string,json_string_end,Box::new(|c,_b|(*c)=='}'),Box::new(|_c,_b|()));

    sm.add_transition(start_state,string_start,Box::new(|c,_b|(*c) == '"'),Box::new(|_c,b|b.clear()));
    sm.add_transition(string_start, string_middle, Box::new(|c,_b|(*c) != '"'), Box::new(|_c,_b|()));
    sm.add_transition(string_start, string_end, Box::new(|c,_b|(*c) == '"'), Box::new(|_c,b|{b.pop();}));
    sm.add_transition(string_middle,string_middle,Box::new(|c,_b|(*c) != '"'),Box::new(|_c,_b|()));
    sm.add_transition(string_middle,string_end,Box::new(|c,_b|(*c) == '"'),Box::new(|_c,b|{b.pop();}));

    sm.add_transition(start_state, number, Box::new(|c,_b|(*c) >= '0' && (*c) <= '9'), Box::new(|_c,_b|()));
    sm.add_transition(number,number_end,Box::new(|c,_b|(*c) < '0' || (*c) > '9'),Box::new(|_c,_b|()));

    sm.add_transition(start_state,file_state,Box::new(|c,_buffer|(*c) == '.'||(*c) == '/' ),Box::new(|_c,_buffer|()));
    sm.add_transition(c_state, file_state, Box::new(|c,_buffer|(*c) == ':'), Box::new(|_c,_buffer|()));
    sm.add_transition(file_state, file_state, Box::new(|c,_b|((*c) >= 'a' && (*c) <= 'z')||((*c) >= 'A' && (*c) <= 'Z')||(*c) == '_'||(*c) == '/'||(*c) == '\\'||(*c) == '.'), Box::new(|_c,_b|()));
    sm.add_transition(file_state,file_ending_state, Box::new(|c,_buffer|(*c) == ' '||(*c) == ';'),  Box::new(|_c,_buffer|()));

    let mut i = 0;
    for char in command_chars{
        let result = sm.transition(&char);
        if let Err(err) = result {
            match err {
                StateMachineError::TransitionNotFound => {
                    return Err(format!("Syntax Error at position {}",i).to_string());
                }
                StateMachineError::StateNotFound => {
                    return Err("State not Found".to_string());
                }
            }
        }
        if let Ok(_) = result {
            if sm.get_current_state_id() == close_state {
                ret.push(Keywords::CloseKeyword);
                sm.reset()
            } else if sm.get_current_state_id() == convert_state {
                ret.push(Keywords::ConvertKeyword);
                sm.reset()
            } else if sm.get_current_state_id() == open_state{
                ret.push(Keywords::OpenKeyword);
                sm.reset()
            } else if sm.get_current_state_id() == file_ending_state{
                let file = sm.get_buffer().into_iter().collect();
                ret.push(Keywords::File(file));
                sm.reset()
            } else if sm.get_current_state_id() == option_state {
                ret.push(Keywords::OptionKeyword);
                sm.reset()
            } else if sm.get_current_state_id() == into_state {
                ret.push(Keywords::IntoKeyword);
                sm.reset()
            } else if sm.get_current_state_id() == generate_state {
                ret.push(Keywords::GenerateKeyword);
                sm.reset();
            } else if sm.get_current_state_id() == setup_state {
                ret.push(Keywords::SetupKeyword);
                sm.reset();
            } else if sm.get_current_state_id() == json_string_end {
                let json = sm.get_buffer().into_iter().collect();
                ret.push(Keywords::JsonStringKeyword(json));
                sm.reset();
            } else if sm.get_current_state_id() == string_end {
                let s = sm.get_buffer().into_iter().collect();
                ret.push(Keywords::String(s));
                sm.reset()
            } else if sm.get_current_state_id() == command_end {
                break;
            } else if sm.get_current_state_id() == record_state {
                ret.push(Keywords::RecordKeyword);
                sm.reset();
            }
        }
        i += 1;
    }

    Ok(ret)
}



 #[cfg(test)]
 mod parser_tests{
    use std::result;

    use super::{parse, parseToken, Keywords};
    use crate::message_parser::commands::Commands::{Open,Convert,ConvertOptions,Close};

    #[test]
    fn open_keyword_test(){
        let chars = "OPEN".chars();
        let result = parseToken(chars);
        if let Ok(res) = result{
            let first_option = res.get(0);
            if let Some(first) = first_option{
                if let Keywords::OpenKeyword = first {
                            
                } else {
                    assert!(false,"wrong Keyword found")
                }
            } else{
                assert!(false,"none found")
            }
        } else if let Err(error) = result {
            assert!(false,"Keyword not found {}",error)
        }
    }
    #[test]
    fn close_keyword_test(){
        let chars = "CLOSE".chars();
        let result = parseToken(chars);
        if let Ok(res) = result{
            let first_option = res.get(0);
            if let Some(first) = first_option{
                if let Keywords::CloseKeyword = first {
                            
                } else {
                    assert!(false,"wrong Keyword found")
                }
            } else{
                assert!(false,"none found")
            }
        } else {
            assert!(false,"Keyword not found")
        }
    }
    #[test]
    fn convert_keyword_test(){
        let chars = "CONVERT".chars();
        let result = parseToken(chars);
        if let Ok(res) = result{
            let first_option = res.get(0);
            if let Some(first) = first_option{
                if let Keywords::ConvertKeyword = first {
                            
                } else {
                    assert!(false,"wrong Keyword found")
                }
            } else{
                assert!(false,"none found")
            }
        } else {
            assert!(false,"Keyword not found")
        }
    }

    #[test]
    fn file_keyword_test(){
        let chars = "./hallo.txt ".chars();
        let result = parseToken(chars);
        if let Ok(res) = result {
            let first_file = res.get(0);
            if let Some(first) = first_file {
                if let Keywords::File(f) = first {
                    assert_eq!(f,"./hallo.txt ");
                } else {
                    assert!(false,"wrong Keyword found")
                }
            } else {
                assert!(false,"none found")
            }
        } else if let Err(error) = result{
            assert!(false,"Keyword not found {}",error)
        }
    }
    #[test]
    fn option_keyword_test(){
        let chars = "OPTION".chars();
        let result = parseToken(chars);
        if let Ok(res) = result {
            let first_option = res.get(0);
            if let Some(first) = first_option {
                if let Keywords::OptionKeyword = first {

                } else {
                    assert!(false,"wrong Keyword found")
                }
            } else {
                assert!(false,"none found")
            }
        } else if let Err(error) = result{
            assert!(false,"Keyword not found {}",error)
        }
    }

    #[test]
    fn into_keyword_test(){
        let chars = "INTO".chars();
        let result = parseToken(chars);
        if let Ok(res) = result{
            let first_into = res.get(0);
            if let Some(first) = first_into {
                if let Keywords::IntoKeyword = first {
                    
                } else {
                    assert!(false,"wrong Keyword found")
                }
            } else {
                assert!(false,"none found")
            }
        } else if let Err(error) = result{
            assert!(false,"Keyword not found {}",error)
        }
    }
    #[test]
    fn string_keyword_test(){
        let chars = "\"Hallo Welt\"".chars();
        let result = parseToken(chars);
        if let Ok(res) = result{
            let first_into = res.get(0);
            if let Some(first) = first_into{
                if let Keywords::String(s) = first {
                    assert_eq!(s,"Hallo Welt")
                } else {
                    assert!(false,"wrong Keyword found")
                }
            } else {
                assert!(false,"none found")
            }
        } else if let Err(error) = result {
            assert!(false,"Keyword not found {}",error)
        }
    }
    #[test]
    fn empty_string_keyword_test(){
        let chars = "\"\"".chars();
        let result = parseToken(chars);
        if let Ok(res) = result{
            let first_into = res.get(0);
            if let Some(first) = first_into{
                if let Keywords::String(s) = first {
                    assert_eq!(s,"")
                } else {
                    assert!(false,"wrong Keyword found")
                }
            } else {
                assert!(false,"none found")
            }
        } else if let Err(error) = result {
            assert!(false,"Keyword not found {}",error)
        }
    }
    #[test]
    fn record_keyword_test(){
        let chars = "RECORD".chars();
        let result = parseToken(chars);
        if let Ok(res) = result {
            let first_into = res.get(0);
            if let Some(first) = first_into{
                if let Keywords::RecordKeyword = first{
                } else {
                    assert!(false,"wrong Keyword found")
                }
            } else {
                assert!(false,"none found")
            }
        } else if let Err(error) = result {
            assert!(false,"Keyword not found {}",error)
        }
    }

    /*
    OPEN [file];
    CONVERT [file1] INTO [file2] USING [converter] WITH [converter config FILE | (config=>value,...)];
    CONVERT OPTIONS [file1];
    DRAW DIAGRAM WITH x=[xproperty] AND y=[yproperty[|color],...] WHERE
    GET POINTS WITH x=[xproperty] AND y=[yproperty[|color],...] WHERE
    CLOSE [file]
    RECORD string
    RECORD OPTIONS
    GENERATE SETUP [GAME] [CAR] [TRACK] [OPTIONS]
    */

    #[test]
    fn open_test(){
        let result = parse("OPEN \"test.sqlite\";");
        match result{
            Ok(command) => {
                match command {
                    Open(open_param) => assert_eq!(open_param.file,"test.sqlite"),
                    _ => assert!(false,"wrong command returned")
                }
            },
            Err(error) => assert!(false,"Error at Function {}",error)
        }
    }
    #[test]
    fn close_test(){
        let result = parse("CLOSE \"test.sqlite\";");
        match result{
            Ok(command) => {
                match command {
                    Close(open_param) => assert_eq!(open_param.file,"test.sqlite"),
                    _ => assert!(false,"wrong command returned")
                }
            },
            Err(error) => assert!(false,"Error at Function {}",error)
        }
    }
    #[test]
    fn convert_test_1(){
        let result = parse("CONVERT file1.sqlite INTO file2.sqlite USING f1_2022 WITH ./config.json;");
        match result{
            Ok(command) => {
                match command {
                    Convert(_convert_params) => assert!(true),
                    _ => assert!(false,"wrong command returned")
                }
            },
            _ => assert!(false,"Error at Function")
        }
    }
    #[test]
    fn convert_test_2(){
        let result = parse("CONVERT file1.sqlite INTO file2.sqlite USING f1_2022 WITH (config=>value,aa=>bb);");
        match result{
            Ok(command) => {
                match command {
                    Convert(_convert_params) => assert!(true),
                    _ => assert!(false,"wrong command returned")
                }
            },
            _ => assert!(false,"Error at Function")
        }
    }
    #[test]
    fn convert_test_3(){
        let result = parse("CONVERT file1.sqlite INTO file2.sqlite USING f1_2022;");
        match result{
            Ok(command) => {
                match command {
                    Convert(_convert_params) => assert!(true),
                    _ => assert!(false,"wrong command returned")
                }
            },
            _ => assert!(false,"Error at Function")
        }
    }

    #[test]
    fn convert_options_test(){
        let result = parse("CONVERT OPTIONS test.sqlite;");
        match result{
            Ok(command) => {
                match command {
                    ConvertOptions(convert_options_params) => {
                        assert_eq!(convert_options_params.file,"test.sqlite");
                        //assert!(true)
                    },
                    _ => assert!(false,"wrong command returned")
                }
            },
            _ => assert!(false,"Error at Function")
        }
    }
 }