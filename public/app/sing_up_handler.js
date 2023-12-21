const button = document.getElementById('sign_in');
const form = document.getElementById('form_login');


form.addEventListener('click', async _ => {
    console.log(1);
    const pass = document.getElementById('floatingPassword');
    const email = document.getElementById('floatingInput');

    const user = {
        email: email.value,
        password: pass.value
    };
    console.log(JSON.stringify(user))
    const response = await fetch(`http://localhost:8080/user/login`, {
        method: 'POST',
        body: JSON.stringify(user)
    });

    const User = await response.json()
    localStorage.setItem("user_id", User.user_id)
    localStorage.setItem("name", User.name)
    localStorage.setItem("surname", User.surname)
    localStorage.setItem("email", User.email)
    localStorage.setItem("token", User.token)
    if (response.status === 200) {
        location.replace("http://localhost:8080/app/index.html");
    }


});
