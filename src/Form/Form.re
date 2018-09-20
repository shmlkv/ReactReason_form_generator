type validator =
  | Required
  | MaxLength(int)
  | Text(string)
  | Placeholder(string);

type field =
  | InputText(string, list(validator))
  | InputEmail(string, list(validator))
  | InputPassword(string, list(validator))
  | Number(string, list(validator))
  | Checkbox(string, list(validator))
  | Radio(string, list(validator))
  | Button(string, list(validator));

let generateInputs = (t: string, name: string, validators: list(validator)) => {
  let valid =
    List.map(
      validator =>
        switch (validator) {
        | Required => ("required", "true")
        | MaxLength(count) => ("maxLength", count->string_of_int)
        | Text(text) => ("value", text)
        | Placeholder(text) => ("placeholder", text)
        },
      validators,
    );
  let input = <input name type_=t />;

  ReasonReact.cloneElement(
    input,
    ~props=Obj.magic(valid->Js.Dict.fromList),
    [||],
  );
};

let render = field =>
  switch (field) {
  | InputText(name, validators) => generateInputs("input", name, validators)
  | InputEmail(name, validators) => generateInputs("email", name, validators)
  | InputPassword(name, validators) =>
    generateInputs("password", name, validators)
  | Number(name, validators) => generateInputs("number", name, validators)
  | Checkbox(name, validators) =>
    generateInputs("checkbox", name, validators)
  | Radio(name, validators) => generateInputs("radio", name, validators)
  | Button(name, validators) => generateInputs("button", name, validators)
  };

let xs = [
  InputEmail("email", [Required, Placeholder("Email")]),
  InputPassword(
    "password",
    [Required, MaxLength(4), Placeholder("Password (<4 chars)")],
  ),
  Button("name", [Text("Login")]),
];

let result = List.map(input => input->render, xs);
let component = ReasonReact.statelessComponent("form");

let make = _children => {
  ...component,
  render: _self =>
    <form> result->ArrayLabels.of_list->ReasonReact.array </form>,
};