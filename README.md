# Form generator on ReactReason

Takes \`List of fields:

```
[
  InputEmail("email", [Required, Placeholder("Email")]),
  InputPassword(
    "password",
    [Required, MaxLength(4), Placeholder("Password (<4 chars)")],
  ),
  Button("name", [Text("Login")]),
];
```

and make html form:

![Form example](https://img.vim-cn.com/05/468fef57d27e589e2a8c95e903f290432e3c28.png)
