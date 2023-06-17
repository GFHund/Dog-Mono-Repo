pub trait command{

}


//struct NotInitializedCommandParams{}

pub struct ConvertOptionsCommandParams{
    pub file:String
}

pub struct OpenCommandParams{
    pub file:String
}

pub struct ConvertCommandParams{
    pub from_file: String,
    pub to_file: String,
    pub converter: String,
    pub config_file: Option<String>,
    pub configs: Option<Vec<String>>
}
pub struct CloseCommandParams{
    pub file:String
}

pub struct GenerateSetupParam{
    pub game: String,
    pub car: String,
    pub track: String
}

pub enum Commands{
    NotInitialized,
    Convert(ConvertCommandParams),
    ConvertOptions(ConvertOptionsCommandParams),
    Open(OpenCommandParams),
    Close(CloseCommandParams),
    GenerateSetup(GenerateSetupParam)
}