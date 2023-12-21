const button = document.getElementById('register');
const form = document.getElementById('form_register');


form.addEventListener('submit', async _ => {
    console.log(1);
    const pass = document.getElementById('floatingPassword');
    const email = document.getElementById('floatingInputEmail');
    const name = document.getElementById('floatingInputName');
    const surname = document.getElementById('floatingInputSurname');
    const org_name = document.getElementById('floatingInputOrgName');
    const number_of_workers = document.getElementById('floatingInputNumberOfWorkers');
    const user = {
        name: name.value,
        surname: surname.value,
        email: email.value,
        password: pass.value,
        organization: {
            org_name: org_name.value,
            number_of_workers: parseInt(number_of_workers.value)
        }
    };
    console.log(JSON.stringify(user))
    const response = await fetch(`http://localhost:8080/user`, {
        method: 'POST',
        body: JSON.stringify(user)
    });
    location.replace("http://localhost:8080/app/sign-in.html");
});
